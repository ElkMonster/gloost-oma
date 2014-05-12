
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
#include <Rect.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   Rect

  \brief   A class template because I'm to lazy to write a class from scretch

  \author  Felix Weiszig
  \date    May 2011
  \remarks Lazy mans way to create a new class ;-)
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

Rect::Rect(mathType xMin, mathType xMax, mathType yMin, mathType yMax):
    _pMin(xMin,yMin,-1.0),
    _pMax(xMax,yMax, 1.0)
{
	// insert your code here
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

Rect::Rect(const Point3& pMin, const Point3& pMax):
    _pMin(pMin),
    _pMax(pMax)
{
	// insert your code here
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

Rect::Rect(const Rect& rect):
    _pMin(rect._pMin),
    _pMax(rect._pMax)
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

Rect::~Rect()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Inits the Rect
  \param   ...
  \remarks ...
*/

void
Rect::init()
{
	// insert your code here
}




////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


