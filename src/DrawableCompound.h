
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



#ifndef H_GLOOST_DRAWABLECOMPOUND
#define H_GLOOST_DRAWABLECOMPOUND



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>



namespace gloost
{

  class Mesh;
  class Vbo;



  //  Compound containing a Mesh and a Vbo to use them together

class DrawableCompound
{
	public:

    // class constructor
    DrawableCompound();
    // class constructor
    DrawableCompound(Mesh* mesh);

    // class destructor
	  virtual ~DrawableCompound();


    // sets the Mesh dirty to indicate a change within its content and trigger an Vbo update
	  void setMeshDirty(bool value = true);

    // updates the vbo, necessary if Mesh was changed
	  void updateVbo();


	  // clears the Mesh and removes resources from GPU
	  void clear();


    // replaces the current Mesh with another one
	  void setMesh(Mesh* mesh);

    // returns the Mesh
	  Mesh* getMesh();

    // returns the Vbo
	  Vbo* getVbo();


	  // draws the compound
	  void draw();


	  // draws the compound, but updates the Vbo befor if necessary
	  void updateAndDraw();


	protected:


    Mesh* _mesh;
    Vbo*  _vbo;


    bool _meshDirty;


};


} // namespace gloost


#endif // H_GLOOST_DRAWABLECOMPOUND


