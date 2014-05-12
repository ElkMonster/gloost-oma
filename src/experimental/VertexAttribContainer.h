
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



#ifndef H_GLOOST_VERTEXATTRIBCONTAINER
#define H_GLOOST_VERTEXATTRIBCONTAINER



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>
#include <SharedResource.h>


/// cpp includes
#include <string>



namespace gloost
{

  class Mesh;


  //  VertexAttribContainer

class VertexAttribContainer : public SharedResource
{
	public:


	  struct AttribInfo
	  {
	    AttribInfo(unsigned numElements, unsigned stride, const std::string& name)
	    {
        _numElements   = numElements;
        _stride        = stride;
        _name          = name;
	    }

      // number of elements
	    unsigned _numElements;

	    /// length in bytes for this attribute
	    unsigned _stride;

	    /// name of the attrib location within the shader
	    std::string _name;
	  };



    // class constructor
    VertexAttribContainer();

    // class constructor
    VertexAttribContainer(Mesh* mesh);

    // class destructor
	  virtual ~VertexAttribContainer();


	  // adds a info for an interleaved attrib
	  void addInterleavedAttrib(unsigned numElements,
                              unsigned stride,
                              const    std::string& name);


	  // returns the vector of interleaved attributes
	  std::vector<float>& getInterleavedAttributes();

	  // returns the vector of information for each attrib within the interleaved structure
	  std::vector<AttribInfo>& getInterleavedAttribInfo();


	  // returns the layout of this Attributes to be used in the vertex shader
	  std::string getLayoutString() const;



	protected:


    /// vector of interleaved attributes
    std::vector<float> _interleavedAttributes;

    /// stores information about the interleaved structure
    std::vector<AttribInfo> _interleavedAttribInfo;

};


} // namespace gloost


#endif // H_GLOOST_VERTEXATTRIBCONTAINER


