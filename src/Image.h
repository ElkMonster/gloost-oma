
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



#ifndef H_GLOOST_IMAGE
#define H_GLOOST_IMAGE



/// gloost system includes
#include <SharedResource.h>
#include <gloostMath.h>
#include <gloostConfig.h>


/// cpp includes
#include <string>

#ifndef GLOOST_GNULINUX
#define GLOOST_GNULINUX
#endif

/// contrib includes
#ifdef GLOOST_GNULINUX
  #include <FreeImage.h>
#endif

#ifdef GLOOST_WINDOWS
  #include <windows.h>
  #include <FreeImage/FreeImage.h>
#endif


namespace gloost
{


  class BinaryBundle;

  //  Wrapper for a FIBITMAP of the libFreeImage

class Image : public SharedResource
{
	public:

    // class constructor
    Image(const std::string& fileName);

    // class constructor creating a new Image
    Image(unsigned width,
          unsigned height,
          unsigned bitsPerPixel,
          unsigned componentsPerPixel,
          unsigned char* pixels);



    // class destructor
	  virtual ~Image();


    // init the Image
	  void init();



    // returns the filename of this image
    const std::string& getFileName() const;



	  // returns the width of the image in pixels
	  unsigned getWidth() const;

	  // returns the height of the image in pixels
	  unsigned getHeight() const;

    // returns ratio width/height
	  mathType getAspectRatio() const;



	  // returns the number of bit per pixel
	  unsigned getBitsPerPixel() const;

	  // returns the number of color components per pixel
	  unsigned getComponentsPerPixel() const;

	  // returns true if the Image has pixels
	  bool hasPixels() const;


	  // returns the pixel data of the image
	  unsigned char* getPixelData();

	  // returns the pixel data of the image
	  const unsigned char* getPixelData() const;



    // fills the Image (color components from 0.0 .. 1.0)
    void fill(mathType r, mathType g, mathType b, mathType a);

    // flips an Image horizontally
    void flipH();

    // flips an Image vertically
    void flipV();

    // rotates the image around its center
//    void rotate(mathType angleInDegrees);

    // scales an Image
//    void scale (unsigned width, unsigned height, FREE_IMAGE_FILTER filter);





    // Sets the color of pixel x,y
    void setPixel(unsigned x,
                  unsigned y,
                  mathType r,
                  mathType g,
                  mathType b,
                  mathType a);

    // returns the color of pixel x,y
    vec4 getPixelColor(unsigned x, unsigned y) const;

	private:


    unsigned      _width;
	  unsigned      _height;
	  unsigned      _bitsPerPixel;
	  unsigned      _componentsPerPixel;

    FIBITMAP* _freeImage_bitmap;
    unsigned  _freeImageColorType;
};


} // namespace gloost


#endif // H_GLOOST_IMAGE


