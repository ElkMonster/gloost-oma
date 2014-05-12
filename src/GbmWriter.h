
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



#ifndef H_GLOOST_GBMWRITER
#define H_GLOOST_GBMWRITER


/// gloost includes
#include <MeshWriter.h>


/// cpp includes
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>



namespace gloost
{

  class Mesh;


//////////////////////////////////////////////////////////////////////////////////////////


  //  Writer for Gloost Binary Mesh format v1.0

class GbmWriter : public MeshWriter
{
	public:

    // class constructor
    GbmWriter();

    // class destructor
	  virtual ~GbmWriter();

    // writes a mesh to a file
	  /*virtual*/ bool write(const std::string& filePath, Mesh* mesh);


	protected:

    // writes the file
    virtual bool writeFile(const std::string& filePath, Mesh* mesh);
};


} // namespace gloost


#endif // H_GLOOST_GBMWRITER

