
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
#include <experimental/Vbo4.h>
#include <gloostConfig.h>
#include <experimental/VertexAttribContainer.h>
#include <glErrorUtil.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class Vbo4

  \brief  Vertex Buffer Object with an Vertex Array Object stroring its layout

  \author Felix Weiszig, Henning Gruendl
  \date   November 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

Vbo4::Vbo4(VertexAttribContainer* vertexAttribs, unsigned usageMode):
  MultiGlContext(2),
  _vertexAttribs(vertexAttribs),
  _usageMode(usageMode)
{
  _vertexAttribs->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

Vbo4::~Vbo4()
{
  // delete both resources from all contextes
//  unbind();
  for (unsigned int i=0; i!=GLOOST_SYSTEM_NUM_RENDER_CONTEXTS; ++i)
  {
    removeFromContext(i);
  }

  _vertexAttribs->dropReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief initialize the resource within a context
  \remarks ...
*/

/*virtual*/
bool
Vbo4::initInContext (unsigned int contextId)
{

  CheckErrorsGL("Before gloost::Vbo4::initInContext()");

  // generate and bind a vertex array object
  unsigned vaoHandle = 0;
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);

  setResourceHandleForContext(vaoHandle, contextId, GLOOST_VBO4_RESOURCE_VAO);

  // generate and bind vertex buffer object
  unsigned vboHandle = 0;
  glGenBuffers(1, &vboHandle);
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);

  setResourceHandleForContext(vboHandle, contextId, GLOOST_VBO4_RESOURCE_VBO);

  //
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * _vertexAttribs->getInterleavedAttributes().size(),
               &_vertexAttribs->getInterleavedAttributes().front(),
               _usageMode);



  // define layout for interleaved attribute data
  std::vector<VertexAttribContainer::AttribInfo>& attribInfo = _vertexAttribs->getInterleavedAttribInfo();

  // determine package stride for one interleaved array
  unsigned packageStride = 0;
  for (unsigned int i=0; i!=attribInfo.size(); ++i)
  {
    packageStride += attribInfo[i]._stride;
  }

  unsigned currentStride = 0;
  for (unsigned int i=0; i!=attribInfo.size(); ++i)
  {
    // enable a VertexAttributeArray
    glEnableVertexAttribArray(i);

    glVertexAttribPointer(i,
                          attribInfo[i]._numElements, // number of components
                          GL_FLOAT,
                          GL_FALSE,
                          packageStride,
                          BUFFER_OFFSET(currentStride));

    currentStride += attribInfo[i]._stride;
  }

  CheckErrorsGL("After gloost::Vbo4::initInContext()");

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Removes a resource from a context
  \remarks ...
*/

/*virtual*/
void
Vbo4::removeFromContext(unsigned int contextId)
{
  if (handleInContextExists(contextId, GLOOST_VBO4_RESOURCE_VBO))
  {
    glDeleteBuffers(1, &getResourceHandleForContext(contextId, GLOOST_VBO4_RESOURCE_VBO));
    setResourceHandleForContext(0, contextId);
  }

  if (handleInContextExists(contextId, GLOOST_VBO4_RESOURCE_VAO))
  {
    glDeleteVertexArrays(1, &getResourceHandleForContext(contextId, GLOOST_VBO4_RESOURCE_VAO));
    setResourceHandleForContext(0, contextId);
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   binds the drawable into state by specify its components
  \remarks ...
*/

/*virtual*/
void
Vbo4::bind(unsigned int contextId)
{
  if (!handleInContextExists(contextId, GLOOST_VBO4_RESOURCE_VAO))
  {
    initInContext(contextId);
  }

  glBindVertexArray(getResourceHandleForContext(contextId, GLOOST_VBO4_RESOURCE_VAO));
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief removes this drawable from state
  \remarks ...
*/

/*virtual*/
void
Vbo4::unbind(unsigned int contextId)
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the VertexAttribContainer used by this Vbo4
  \remarks ...
*/


VertexAttribContainer*
Vbo4::getVertexAttribContainer()
{
  return _vertexAttribs;
}


////////////////////////////////////////////////////////////////////////////////



} // namespace gloost
