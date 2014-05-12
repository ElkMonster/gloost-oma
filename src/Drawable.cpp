
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
#include <Drawable.h>
#include <Mesh.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class Drawable

  \brief Base class of all drawables like Vbo or DisplayList

  \author Felix Weiszig
  \date   January 2011
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor
  \param numResourcesPerContext
  \param geometry gloost::Geometry container
  \remarks ...
*/

Drawable::Drawable(unsigned int numResourcesPerContext, Mesh* mesh):
  MultiGlContext(numResourcesPerContext),
  _mesh(mesh),
  _drawMode(GLOOST_DRAWABLE_SUGGESTED_DRAWMODE),
  _suggestedDrawMode(GLOOST_DRAWABLE_SUGGESTED_DRAWMODE)
{
  _mesh->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

/*virtual*/
Drawable::~Drawable()
{
  _mesh->dropReference();
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief Increments the reference counter
*/

/*virtual*/
Drawable*
Drawable::takeReference()
{
  _mesh->takeReference();
	SharedResource::takeReference();
	return this;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief Decrements the reference counter
*/

/*virtual*/
void
Drawable::dropReference()
{
  _mesh->dropReference();
  SharedResource::dropReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Returns the Geometry container used by this Drawable
  \param ...
  \remarks ...
*/

Mesh*
Drawable::getMesh()
{
	return _mesh;
}




////////////////////////////////////////////////////////////////////////////////


/**
  \brief Sets the draw mode of this Drawable. (GL_TRIANGLES, GL_POINTS, ...) Default is GL_TRIANGLES
  \param ...
  \remarks ...
*/

/*virtual*/
void
Drawable::setDrawMode(unsigned int drawMode)
{
  if (drawMode == GLOOST_DRAWABLE_SUGGESTED_DRAWMODE)
  {
    _drawMode = _suggestedDrawMode;
  }
  else
  {
    _drawMode = drawMode;
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Returns the draw mode of this Drawable
  \param ...
  \remarks ...
*/

/*virtual*/
unsigned int
Drawable::getDrawMode() const
{
	return _drawMode;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the draw mode suggested by analysing the mesh of this Drawable
  \param ...
  \remarks This will return GL_POINTS till you call Drawable::initInContext() or
           bind() once.
*/

/*virtual*/
unsigned int
Drawable::getSuggestedDrawMode() const
{
	return _suggestedDrawMode;
}


////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


