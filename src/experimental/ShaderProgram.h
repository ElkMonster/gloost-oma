
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



#ifndef H_GLOOST_SHADERPROGRAM
#define H_GLOOST_SHADERPROGRAM



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>
#include <MultiGlContext.h>


/// cpp includes
#include <string>
#include <map>
#include <GL/glew.h>



#define GLOOST_SHADERPROGRAM_UNDEFINED_SHADER       0
#define GLOOST_SHADERPROGRAM_VERTEX_SHADER          GL_VERTEX_SHADER
#define GLOOST_SHADERPROGRAM_GEOMETRY_SHADER        GL_GEOMETRY_SHADER
#define GLOOST_SHADERPROGRAM_FRAGMENT_SHADER        GL_FRAGMENT_SHADER
#define GLOOST_SHADERPROGRAM_TESS_CONTROL_SHADER    GL_TESS_CONTROL_SHADER
#define GLOOST_SHADERPROGRAM_TESS_EVALUATION_SHADER GL_TESS_EVALUATION_SHADER



namespace gloost
{


  //  GLSL shader supporting openGl 4.0 features

class ShaderProgram: public MultiGlContext
{
	public:

    // class constructor
    ShaderProgram();

    // class destructor
	  virtual ~ShaderProgram();


	  // attaches a specific shader type to be bound
    bool attachShader (unsigned shaderType, const std::string& fileName);


    // reloads all shader source files and updates the ShaderProgram on the GPU
    void reloadShaders();


    // inits the ShaderProgram for a specific context
	  virtual bool initInContext(unsigned contextId = 0);

    // remove a resource from a context
	  virtual void removeFromContext(unsigned int contextId = 0);


    // Return the shader handle
    unsigned int getHandle(unsigned int contextId = 0);

    // Set/unset the Shader for following geometry
    void set(unsigned int contextId = 0);

    // disable all GLSL shader rendering
    static void disable();


	protected:


	  struct ShaderComponent
	  {
	    ShaderComponent()
	    {
        _fileName      = "no name";
        _type          = GLOOST_SHADERPROGRAM_UNDEFINED_SHADER;
        _source        = "";
        _handle        = 0;
        _compileStatus = GL_FALSE;
	    }

	    ShaderComponent(const std::string& fileName, unsigned type, const std::string& source)
	    {
        _fileName      = fileName;
        _type          = type;
        _source        = source;
        _handle        = 0;
        _compileStatus = GL_FALSE;
	    }

	    ShaderComponent(const ShaderComponent& component)
	    {
        _fileName      = component._fileName;
        _type          = component._type;
        _source        = component._source;
        _handle        = component._handle;
        _compileStatus = component._compileStatus;
	    }

	    std::string _fileName;
	    unsigned    _type;
	    std::string _source;
	    GLuint      _handle;
	    GLint       _compileStatus;
	  };


    // loads the source file for a shader
    bool readSourceFile(ShaderComponent& component);

    // compiles a shader and throws error if any
	  void compileShader(ShaderComponent& component);

    std::map<unsigned, ShaderComponent> _components;


    // indicates an error while compiling any shader
    bool _componentCompileError;


    // validates a shader program by using glGetShaderInfoLog
    void validateShader(GLuint shaderHandle, const std::string& shaderFileName);

};


} // namespace gloost


#endif // H_GLOOST_SHADERPROGRAM


