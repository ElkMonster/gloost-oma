
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).

            gloost is being created by Felix Weißig and Stephan Beck

     Felix Weißig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



/// gloost system includes
#include <experimental/ShaderProgram.h>
#include <BinaryFile.h>
#include <glErrorUtil.h>



/// cpp includes
#include <string>
#include <iostream>




namespace gloost
{

/**
  \class   ShaderProgram

  \brief   GLSL shader supporting openGl 4.0 features

  \author  Felix Weiszig, Henning Gruendl
  \date    November 2011
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

ShaderProgram::ShaderProgram():
    MultiGlContext(1),
    _components(),
    _componentCompileError(GL_FALSE)
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

ShaderProgram::~ShaderProgram()
{
  for (unsigned int i=0; i!=GLOOST_SYSTEM_NUM_RENDER_CONTEXTS; ++i)
  {
    removeFromContext(i);
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   attaches a specific shader type to be bound
  \param   ...
  \remarks ...
*/

/*virtual*/
bool
ShaderProgram::attachShader(unsigned shaderType, const std::string& fileName)
{
  ShaderComponent component(fileName, shaderType, "");
  _components[shaderType] = component;
  return readSourceFile(_components[shaderType]);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   reloads all shader source files and updates the ShaderProgram on the GPU
  \param   ...
  \remarks ...
*/

/*virtual*/
void
ShaderProgram::reloadShaders()
{
  std::map<unsigned, ShaderComponent>::iterator componentIt    = _components.begin();
  std::map<unsigned, ShaderComponent>::iterator componentEndIt = _components.end();

  for (; componentIt!=componentEndIt; ++componentIt)
  {
    readSourceFile((*componentIt).second);
  }

  for (unsigned int i=0; i!=GLOOST_SYSTEM_NUM_RENDER_CONTEXTS; ++i)
  {
    removeFromContext(i);
  }
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Inits the ShaderProgram
  \param   ...
  \remarks ...
*/

/*virtual*/
bool
ShaderProgram::initInContext(unsigned contextId)
{

  if (handleInContextExists(contextId))
  {
    removeFromContext(contextId);
  }


  std::map<unsigned, ShaderComponent>::iterator componentIt    = _components.begin();
  std::map<unsigned, ShaderComponent>::iterator componentEndIt = _components.end();

  for (; componentIt!=componentEndIt; ++componentIt)
  {
    compileShader((*componentIt).second);
  }

  unsigned int shaderHandle = glCreateProgram();


  /// make a association between the context and the GL handle of this shader
  setResourceHandleForContext(shaderHandle, contextId);


  // attach components to shader program
  componentIt    = _components.begin();

  for (; componentIt!=componentEndIt; ++componentIt)
  {
    /// attache programs to shaderh handle
    CheckErrorsGL(("Befor attaching " + (*componentIt).second._fileName + " on SR " + gloost::toString(getSharedResourceId())).c_str());
    glAttachShader( shaderHandle, (*componentIt).second._handle );
    CheckErrorsGL(("After attaching " + (*componentIt).second._fileName + " on SR " + gloost::toString(getSharedResourceId())).c_str());
  }


  /// link components to a shader program
  glLinkProgram(shaderHandle);



#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
  if (!_componentCompileError)
  {
    std::cout << std::endl;
    std::cout << std::endl << "Message from Shader::compileToProgram() on SharedResource " << getSharedResourceId() << ":";
    std::cout << std::endl << "             Successfully compiled and linked.";

    componentIt    = _components.begin();
    for (; componentIt!=componentEndIt; ++componentIt)
    {
      /// attache programs to shaderh handle
      std::cerr << std::endl << "             " << (*componentIt).second._fileName;
    }

    std::cout << std::endl;
    return true;
  }
#endif

  return false;
}


///////////////////////////////////////////////////////////////////////////////

/**
  \brief Removes a ShaderProgram from a context

  \param contextId id of the context, the shader will be removed from. Use 0 or no
         argument if you work with only one context.

  \remarks If you call set() on this ShaderProgram, it will be automaticly initialized
           for the context again
*/

/*virtual*/
void
ShaderProgram::removeFromContext(unsigned int contextId)
{
  if (handleInContextExists(contextId))
  {
    glDeleteObjectARB(getResourceHandleForContext(contextId));
    setResourceHandleForContext(0, contextId);
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   loads the source file for a shader
  \param   ...
  \remarks ...
*/

/*virtual*/
bool
ShaderProgram::readSourceFile(ShaderComponent& component)
{
  unsigned char* buffer           = 0;
  unsigned int   bufferSizeInByte = 0;

  if (!gloost::BinaryFile::read(component._fileName, buffer, bufferSizeInByte))
  {
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_WARNINGS
        std::cerr << std::endl;
        std::cerr << std::endl << "Warning from ShaderProgram::readSourceFile() on SharedResource " << getSharedResourceId() << ":";
        std::cerr << std::endl << "             Could NOT load source file \"" << component._fileName << "\"";
        std::cerr << std::endl;
#endif
    return false;
  }
  else
  {
    char* shaderSource = new char[bufferSizeInByte+1];
    memcpy(shaderSource, buffer, bufferSizeInByte);
    shaderSource[bufferSizeInByte] = '\0';

    component._source = std::string(shaderSource);

    delete buffer;
    delete shaderSource;

    return true;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////

/**
  \brief compiles a shader and throws error if any
  \remarks ...
*/


void
ShaderProgram::compileShader(ShaderComponent& component)
{
  component._handle = glCreateShader(component._type);

  const char* source = component._source.c_str();
  glShaderSource(component._handle, 1, &source, NULL);

  glCompileShader(component._handle);
  glGetShaderiv(component._handle, GL_COMPILE_STATUS, &component._compileStatus);


  if (component._compileStatus == GL_FALSE)
  {
    _componentCompileError = true;

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl;
    std::cout << std::endl << "ERROR in ShaderProgram::compileShader on SharedResource " << getSharedResourceId() << ":";
    std::cout << std::endl << "         Can't compile shader \"" << component._fileName << "\"";
    std::cout << std::endl;
#endif
  }

  // validate the vertex shader and print compiler log
  validateShader(component._handle, component._fileName);
}


///////////////////////////////////////////////////////////////////////////////////////////////


/**
  \brief Validates a shader program by using glGetShaderInfoLog

  \param shaderHandle OpenGL handle of this shader
  \param shaderFileName The name of the shader source file, just for output purpose

  \remarks On ATI cards there will be always a message that the shader was build correctly
*/
void
ShaderProgram::validateShader(GLuint shaderHandle, const std::string& shaderFileName)
{
  const unsigned int BUFFER_SIZE = 2048;
  char               buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  GLsizei length = 0;

  glGetShaderInfoLog(shaderHandle, BUFFER_SIZE, &length, buffer);
  if (length > 0)
  {

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl;
    std::cout << std::endl << "Message from ShaderProgram::validateShader on SharedResource " << getSharedResourceId() << ":";
    std::cout << std::endl << "             Compile error(s)/warning(s) in file \"" << shaderFileName << "\" !";
    std::cout << std::endl;
    std::cout << std::endl << buffer;
    std::cout << std::endl;
    std::cout << std::endl;
#endif

  }
}


///////////////////////////////////////////////////////////////////////////////////////////////


/**
  \brief Returns the OpenGL shader handle for a specified context

  \param contextId The context id of the context you want the handle from. Use 0 or no
         argument if you work with only one context.

  \remarks The shader will be initialized for the context if not allready done
*/

unsigned int
ShaderProgram::getHandle(unsigned int contextId)
{
  if (!handleInContextExists(contextId))
  {
    initInContext(contextId);
  }
  return getResourceHandleForContext(contextId);
}


///////////////////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Binds/sets the shader into the specified GL state

  \param   contextId The context id of the context you want the shader set to. Use 0 or no
           argument if you work with only one context.

  \remarks The shader will be initialized for the context if not allready done
*/
void
ShaderProgram::set(unsigned int contextId)
{
  if (!handleInContextExists(contextId))
  {
    initInContext(contextId);
  }

  // SetShader
  glUseProgram(getResourceHandleForContext(contextId));
}


///////////////////////////////////////////////////////////////////////////////////////////////


/**
  \brief Disable all GLSL shader rendering and fall back to the standard pipeline

  \param contextId The context id of the context you want the shader set to. Use 0 or no
         argument if you work with only one context.

  \remarks all texture units will be cleared and all texture matrices will be set to identity.
*/


/*static*/
void
ShaderProgram::disable()
{
  glUseProgram(0);
}


///////////////////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


