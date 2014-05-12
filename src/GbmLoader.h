
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



#ifndef H_GLOOST_GBMLOADER
#define H_GLOOST_GBMLOADER


/// gloost includes
#include <MeshLoader.h>


/// cpp includes
#include <string>
#include <vector>



namespace gloost
{

  class Mesh;


//////////////////////////////////////////////////////////////////////////////////////////


  //  Loader for gloost Binary Mesh format

class GbmLoader : public MeshLoader
{
	public:

    // class constructor
    GbmLoader(const std::string& filePath);

    // class destructor
	  virtual ~GbmLoader();


	protected:

    /// Struct Stores a Gloost Binary File feature and an the number of elements
    struct GbmFeature
    {
      std::string  name;
      unsigned int count;
      unsigned int count2;
    };


    // read the file
    virtual bool readFile(const std::string& filePath);
};


} // namespace gloost


#endif // H_GLOOST_GBMLOADER

