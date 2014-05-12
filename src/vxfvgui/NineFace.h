
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



#ifndef H_GLOOST_NINEFACE
#define H_GLOOST_NINEFACE



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>



namespace gloost
{


  //  Specifies a segmentation of a rectangle into 9 areas defined by left, right, top and bottom

class NineFace
{
	public:

    // class constructor
    NineFace(float width, float height,
             float left, float right,
             float top, float bottom);

    // class destructor
	  virtual ~NineFace();

    float _width;
    float _height;
	  float _left;
	  float _right;
	  float _top;
	  float _bottom;

	protected:

};


} // namespace gloost


#endif // H_GLOOST_NINEFACE


