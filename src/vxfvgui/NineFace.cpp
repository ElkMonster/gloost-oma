
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
#include <vxfvgui/NineFace.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   NineFace

  \brief   Specifies a segmentation of a rectangle into 9 areas defined by left, right, top and bottom

  \author  Felix Weiszig
  \date    September 2011
  \remarks \code
        left        right
        ----------------          ---
        |   |       |  | top
        |---|-------|--|
        |   |       |  |          height
        |   |       |  |
        |---|-------|--|
        |   |       |  | bottom
        ----------------          ---

        |     width    |

  \endcode
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

NineFace::NineFace(float width, float height,
                   float left, float right,
                   float top, float bottom):
     _width(),
     _height(),
	   _left(),
	   _right(),
	   _top(),
	   _bottom()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

NineFace::~NineFace()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


