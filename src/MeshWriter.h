
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



#ifndef H_GLOOST_MESHWRITER
#define H_GLOOST_MESHWRITER


/// gloost includes
#include <string.h>


/// cpp includes
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>



namespace gloost
{

  class Mesh;


//////////////////////////////////////////////////////////////////////////////////////////


  //  Base class of all mesh writers

class MeshWriter
{
	public:

    // class constructor
    MeshWriter();

    // class destructor
	  virtual ~MeshWriter();

    // writes a mesh to a file
	  virtual bool write(const std::string& filePath, Mesh* mesh) = 0;


	protected:

    // writes the file
    virtual bool writeFile(const std::string& filePath, Mesh* mesh) = 0;
};


} // namespace gloost


#endif // H_GLOOST_MESHWRITER

