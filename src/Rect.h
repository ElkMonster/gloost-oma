
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



#ifndef H_GLOOST_RECT
#define H_GLOOST_RECT



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>



namespace gloost
{


  //  An axis aligned rectangle

class Rect
{
	public:

    // class constructor
    Rect(mathType xMin, mathType xMax, mathType yMin, mathType yMax);

    /// class constructor
    Rect(const Point3& pMin, const Point3& pMax);

    /// class constructor
    Rect(const Rect& rect);

    // class destructor
	  ~Rect();


    // init the EmptyClass
	  void init();


	private:

    Point3 _pMin;
    Point3 _pMax;

};


} // namespace gloost


#endif // GLOOST_EMPTYCLASS_H


