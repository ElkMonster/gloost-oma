
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
#include <experimental/Ibo.h>
#include <gloostConfig.h>
#include <Mesh.h>
#include <glErrorUtil.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class Ibo

  \brief  Index Buffer Object

  \author Felix Weiszig, Henning Gruendl
  \date   November 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

Ibo::Ibo(Mesh* mesh, unsigned drawMode):
  MultiGlContext(1),
  _mesh(mesh),
  _drawMode(drawMode),
  _suggestedDrawMode(0),
  _numIdices(0)
{
  _mesh->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

Ibo::~Ibo()
{
  // delete both resources from all contextes
//  unbind();
  for (unsigned int i=0; i!=GLOOST_SYSTEM_NUM_RENDER_CONTEXTS; ++i)
  {
    removeFromContext(i);
  }

  _mesh->dropReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief initialize the resource within a context
  \remarks ...
*/

/*virtual*/
bool
Ibo::initInContext (unsigned int contextId)
{

  CheckErrorsGL("Before gloost::Ibo::initInContext()");

  // Triangles indices
  GLuint indexBufferHandle = 0;

  glGenBuffers(1, &indexBufferHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);

  // element array for quads
  if (_mesh->getQuads().size())
  {
    _suggestedDrawMode = GL_QUADS;

    _numIdices = _mesh->getQuads().size() * 4;

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _numIdices * sizeof(unsigned int),
                 &(_mesh->getQuads().front()),
                 GL_STATIC_DRAW);

  }
  // element array for triangles
  else if (_mesh->getTriangles().size())
  {
    _suggestedDrawMode = GL_TRIANGLES;

    _numIdices = _mesh->getTriangles().size() * 3;

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _numIdices * sizeof(unsigned int),
                 &(_mesh->getTriangles().front()),
                 GL_DYNAMIC_DRAW);

  }
  // element array for lines
  else if (_mesh->getLines().size())
  {
    _suggestedDrawMode = GL_LINES;
    _numIdices = _mesh->getLines().size() * 2;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _numIdices * sizeof(unsigned int),
                 &(_mesh->getLines().front()),
                 GL_STATIC_DRAW);


  }
  // element array for points
  else if (_mesh->getPoints().size())
  {
    _suggestedDrawMode = GL_POINTS;

    _numIdices = _mesh->getPoints().size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _numIdices * sizeof(unsigned int),
                 &(_mesh->getPoints().front()),
                 GL_STATIC_DRAW);
  }


  CheckErrorsGL("After gloost::Ibo::initInContext()");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

  setResourceHandleForContext(indexBufferHandle,
                              contextId,
                              0);

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Removes a resource from a context
  \remarks ...
*/

/*virtual*/
void
Ibo::removeFromContext(unsigned int contextId)
{
  if (handleInContextExists(contextId, 0))
  {
    glDeleteBuffers(1, &getResourceHandleForContext(contextId, 0));
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
Ibo::bind(unsigned int contextId)
{
  if (!handleInContextExists(contextId, 0))
  {
    initInContext(contextId);
  }

  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, getResourceHandleForContext(contextId, 0));
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief removes this drawable from state
  \remarks ...
*/

/*virtual*/
void
Ibo::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Draws only Faces (for shadowmap pass for example)
  \remarks ...
*/

/*virtual*/
void
Ibo::draw()
{
  if (_drawMode == GLOOST_IBO_SUGGESTED_DRAWMODE)
  {
    glDrawElements(_suggestedDrawMode, _numIdices, GL_UNSIGNED_INT, 0);
    return;
  }

  glDrawElements(_drawMode, _numIdices, GL_UNSIGNED_INT, 0);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Draws only Faces (for shadowmap pass for example)
  \remarks ...
*/

///*virtual*/
//void
//Ibo::draw(int startIndex, int endIndex, unsigned int contextId)
//{
//  if (_drawMode == GLOOST_IBO_SUGGESTED_DRAWMODE)
//  {
//    glDrawRangeElements(_suggestedDrawMode,
//                        startIndex,
//                        endIndex,
//                        (int)endIndex-(int)startIndex,
//                        GL_UNSIGNED_INT,
//                        0);
//    return;
//  }
//
//  glDrawRangeElements(_drawMode,
//                      startIndex,
//                      endIndex,
//                      (int)endIndex-(int)startIndex,
//                      GL_UNSIGNED_INT,
//                      0);
//}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the VertexAttribContainer used by this Ibo
  \remarks ...
*/


Mesh*
Ibo::getMesh()
{
  return _mesh;
}


////////////////////////////////////////////////////////////////////////////////



} // namespace gloost
