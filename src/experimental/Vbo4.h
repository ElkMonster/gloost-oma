
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



#ifndef H_GLOOST_VBO4
#define H_GLOOST_VBO4


/// cpp includes
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <map>

/// gloost includes
#include <MultiGlContext.h>


#define GLOOST_VBO4_RESOURCE_VAO            0 // vertex array object
#define GLOOST_VBO4_RESOURCE_VBO            1 // vertex buffer object


#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif


namespace gloost
{

  class VertexAttribContainer;

////////////////////////////////////////////////////////////////////////////////


  //  Vertex Buffer Object with an Vertex Array Object stroring its layout

class Vbo4 : public MultiGlContext
{
	public:

    // class constructor
    Vbo4(VertexAttribContainer* vertexAttribs, unsigned usageMode = GL_STATIC_DRAW);

    // class destructor
	  virtual ~Vbo4();


    // bind the drawable into state by specify its attributes
    virtual void bind(unsigned int contextId = 0);

    // remove this drawable from state
	  virtual void unbind(unsigned int contextId = 0);



	  // initialize the resource within a context
	  virtual bool initInContext (unsigned int contextId = 0);

	  // remove a resource from a context
	  virtual void removeFromContext(unsigned int contextId = 0);


    // returns the VertexAttribContainer used by this Vbo4
    VertexAttribContainer* getVertexAttribContainer();


	protected:

	  VertexAttribContainer* _vertexAttribs;

	  unsigned _usageMode;
};


} // namespace gloost


#endif // H_GLOOST_VBO4





