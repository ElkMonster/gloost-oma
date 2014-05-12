
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



#ifndef H_GLOOST_IBO
#define H_GLOOST_IBO


/// cpp includes
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <map>

/// gloost includes
#include <MultiGlContext.h>


#define GLOOST_IBO_SUGGESTED_DRAWMODE 2368929


namespace gloost
{

  class Mesh;

////////////////////////////////////////////////////////////////////////////////


  //  Vertex Buffer Object with an Vertex Array Object stroring its layout

class Ibo : public MultiGlContext
{
	public:

    // class constructor
    Ibo(Mesh* mesh, unsigned drawMode = GLOOST_IBO_SUGGESTED_DRAWMODE);

    // class destructor
	  virtual ~Ibo();


    // bind the drawable into state by specify its attributes
    virtual void bind(unsigned int contextId = 0);

    // remove this drawable from state
	  virtual void unbind();


	  // draws the VBO with bound components
	  /*virtual*/ void draw();
//	   void draw(int startIndex, int endIndex, unsigned int contextId = 0);


	  // initialize the resource within a context
	  virtual bool initInContext (unsigned int contextId = 0);

	  // remove a resource from a context
	  virtual void removeFromContext(unsigned int contextId = 0);


    // returns the Mesh
    Mesh* getMesh();


	protected:

	  Mesh* _mesh;

	  unsigned _drawMode;
	  unsigned _suggestedDrawMode;
	  unsigned _numIdices;
};


} // namespace gloost


#endif // H_GLOOST_IBO





