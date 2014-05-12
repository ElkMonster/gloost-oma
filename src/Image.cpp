
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
#include <Image.h>
#include <gloostConfig.h>
#include <BinaryBundle.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class Image

  \brief Wrapper for a FIBITMAP of the libFreeImage

  \author Felix Weiszig
  \date   January 2011
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

Image::Image(const std::string& fileName):
    SharedResource(),
    _width(0),
	  _height(0),
	  _bitsPerPixel(0),
    _componentsPerPixel(0),
    _freeImage_bitmap(0),
    _freeImageColorType(0)
{
  //Automatocally detects the format(from over 20 formats!)
  FREE_IMAGE_FORMAT imageFileType = FreeImage_GetFileType(fileName.c_str(),0);

  /// error message if file type is unkown
  if (imageFileType == FIF_UNKNOWN)
  {
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl;
    std::cout << std::endl << "ERROR in Image::Image(const std::string& fileName): (resourceId: " << toString(getSharedResourceId()) << ")";
    std::cout << std::endl << "             Could NOT load image \"" << fileName << "\".";
    std::cout << std::endl << "             File path is wrong or the file has an unsupported file type.";
		std::flush(std::cout);
#endif
    return;
  }

  /// load a FreeImage
	_freeImage_bitmap = FreeImage_Load(imageFileType, fileName.c_str());

	_width              = FreeImage_GetWidth(_freeImage_bitmap);
	_height             = FreeImage_GetHeight(_freeImage_bitmap);
	_bitsPerPixel       = FreeImage_GetBPP(_freeImage_bitmap);
	_freeImageColorType = FreeImage_GetColorType(_freeImage_bitmap);
  _componentsPerPixel = _bitsPerPixel/8;


  FreeImage_FlipVertical(_freeImage_bitmap);




#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
    std::cout << std::endl;
    std::cout << std::endl << "Message from Image::Image(const std::string& fileName): (resourceId: " << toString(getSharedResourceId()) << ")";
    std::cout << std::endl << "             Image \"" << fileName << "\" loaded";
    std::cout << std::endl << "             width: .......        " << _width << " pix";
    std::cout << std::endl << "             height: ......        " << _height << " pix";
    std::cout << std::endl << "             bit per pixel:        " << _bitsPerPixel;
    std::cout << std::endl << "             components per pixel: " << _componentsPerPixel;
		std::flush(std::cout);
#endif


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor creating a new Image
  \remarks ...
*/

Image::Image(unsigned width,
             unsigned height,
             unsigned bitsPerPixel,
             unsigned componentsPerPixel,
             unsigned char*    pixels):
    SharedResource(),
    _width(width),
	  _height(height),
	  _bitsPerPixel(bitsPerPixel),
	  _componentsPerPixel(0),
    _freeImage_bitmap(0),
    _freeImageColorType(0)
{

  /// allocate memory for a new FreeImage bitmap
  _freeImage_bitmap = FreeImage_Allocate(_width, _height, _bitsPerPixel);

  /// determine attributes
	_freeImageColorType = FreeImage_GetColorType(_freeImage_bitmap);

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

/*virtual*/
Image::~Image()
{
  if (_freeImage_bitmap)
  {
    FreeImage_Unload(_freeImage_bitmap);
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Inits the Image
  \param ...
  \remarks ...
*/

void
Image::init()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the width of the image in pixels
  \param ...
  \remarks ...
*/

unsigned int
Image::getWidth() const
{
	return _width;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the height of the image in pixels
  \param ...
  \remarks ...
*/

unsigned int
Image::getHeight() const
{
	return _height;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns ratio width/height
  \param ...
  \remarks ...
*/

mathType
Image::getAspectRatio() const
{
	return _width/(mathType)_height;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the number of bit per pixel
  \param ...
  \remarks ...
*/

unsigned int
Image::getBitsPerPixel() const
{
	return _bitsPerPixel;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the number of color components per pixel
  \param ...
  \remarks ...
*/

unsigned int
Image::getComponentsPerPixel() const
{
	return _bitsPerPixel;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns true if the Image has pixels
  \param ...
  \remarks ...
*/

bool
Image::hasPixels() const
{
	return (bool)_freeImage_bitmap;
}


////////////////////////////////////////////////////////////////////////////////

/**
  \brief returns the pixel data of the image
  \param ...
  \remarks ...
*/

unsigned char*
Image::getPixelData()
{
	return (unsigned char*)FreeImage_GetBits(_freeImage_bitmap);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the pixel data of the image
  \param ...
  \remarks ...
*/

const unsigned char*
Image::getPixelData() const
{
	return (unsigned char*)FreeImage_GetBits(_freeImage_bitmap);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the pixel data of the image
  \param ...
  \remarks ...
*/

vec4
Image::getPixelColor(unsigned x, unsigned y) const
{
  RGBQUAD* color = new RGBQUAD;
  FreeImage_GetPixelColor(_freeImage_bitmap, x, y, color);
  return vec4(color->rgbRed, color->rgbGreen, color->rgbBlue, color->rgbReserved);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   fills the Image with a color
  \param   r red color component between 0.0 ... 1.0
  \param   g green color component between 0.0 ... 1.0
  \param   b blue color component between 0.0 ... 1.0
  \param   a alpha color component between 0.0 ... 1.0
  \remarks ...
*/

void
Image::fill(mathType r, mathType g, mathType b, mathType a)
{
  // FreeImage uses BGRA scheme
  RGBQUAD color;
  color.rgbBlue       = (unsigned int) gloost::clamp(b*255.0, 0.0, 255.0);
  color.rgbGreen      = (unsigned int) gloost::clamp(g*255.0, 0.0, 255.0);
  color.rgbRed        = (unsigned int) gloost::clamp(r*255.0, 0.0, 255.0);
  color.rgbReserved   = (unsigned int) gloost::clamp(a*255.0, 0.0, 255.0);

  FreeImage_FillBackground(_freeImage_bitmap, &color, FI_COLOR_IS_RGBA_COLOR);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   flips an Image horizontally
  \remarks ...
*/

void
Image::flipH()
{
  FreeImage_FlipHorizontal(_freeImage_bitmap);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   flips an Image vertically
  \remarks ...
*/

void
Image::flipV()
{
  FreeImage_FlipVertical(_freeImage_bitmap);
}


////////////////////////////////////////////////////////////////////////////////


///**
//  \brief   rotates the image around its center
//  \remarks ...
//*/
//
//void
//Image::rotate(mathType angleInDegrees)
//{
//  FreeImage_RotateEx(_freeImage_bitmap, angleInDegrees, 0, 0, _width*0.5, _height*0.5, true);
//}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   scales an Image
  \remarks ...
*/

//void
//Image::scale(unsigned width, unsigned height, FREE_IMAGE_FILTER filter)
//{
//  FreeImage_Rescale(_freeImage_bitmap, width, height, filter);
//  _width  = width;
//  _height = height;
//}


//////////////////////////////////////////////////////////////////////////////

/**
  \brief   Sets the color of pixel x,y
  \param   ...
  \remarks ...
*/

void
Image::setPixel(unsigned int x,
                unsigned int y,
                mathType r,
                mathType g,
                mathType b,
                mathType a)
{
  // FreeImage uses BGRA scheme
  RGBQUAD color;
  color.rgbBlue       = (unsigned int) (b*255);
  color.rgbGreen      = (unsigned int) (g*255);
  color.rgbRed        = (unsigned int) (r*255);
  color.rgbReserved   = (unsigned int) (a*255);

  {
    FreeImage_SetPixelColor(_freeImage_bitmap, x, y, &color);
  }

//  FreeImage_F(_freeImage_bitmap, &color);
}


////////////////////////////////////////////////////////////////////////////////

} // namespace gloost


