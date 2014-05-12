
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
#include <Mouse.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Mouse::Mouse():
    _loc(),
    _oldLoc(),
    _speed(),
    _buttonStates(),
    _lastDownPos(),
    _lastUpPos(),
    _mouseDownEvents(),
    _mouseUpEvents()
{


	for(unsigned int i=0; i != 6; ++i)
	{
	  _buttonStates[i]    = false;
	  _mouseDownEvents[i] = false;
	  _mouseUpEvents[i]   = false;
	}

}


///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Mouse::~Mouse()
{
	// insert your code here
}

///////////////////////////////////////////////////////////////////////////////


  /// get the location of the mouse

const Point3&
Mouse::getLoc() const
{
  return _loc;
}


///////////////////////////////////////////////////////////////////////////////


void
Mouse::setLoc(Point3 loc)
{
  _oldLoc = _loc;
  _loc = loc;
  _speed +=  _loc-_oldLoc;
}


///////////////////////////////////////////////////////////////////////////////


void
Mouse::setLoc(float x, float y, float z)
{
  _oldLoc = _loc;
  _loc = Point3(x,y,z);
  _speed += _loc-_oldLoc;
}


///////////////////////////////////////////////////////////////////////////////


  /// get the location of the mouse one frame before

const Point3&
Mouse::getOldLoc() const
{
  return _oldLoc;
}

///////////////////////////////////////////////////////////////////////////////


  /// get the moving speed of the mouse (in pixel/frame)

Point3
Mouse::getSpeed() const
{
  return _speed;
}

///////////////////////////////////////////////////////////////////////////////


  /// get the coordinates of the last mouseUp

const Point3&
Mouse::getLastMouseDownLoc() const
{
  return _lastDownPos;
}

///////////////////////////////////////////////////////////////////////////////


  /// get the coordinates of the last mouseUp

const Point3&
Mouse::getLastMouseUpLoc() const
{
  return _lastUpPos;
}

///////////////////////////////////////////////////////////////////////////////


  /// set the speed of the mouse to zero

void
Mouse::setSpeedToZero()
{
  _speed = Vector3();
}

///////////////////////////////////////////////////////////////////////////////


  /// reset mouse events so they can be set in the next frame

void
Mouse::resetMouseEvents()
{

  // since the mousewheel will create a button down AND a button up each time
  // I don't handle the up event and do the reset here
  _buttonStates[GLOOST_MOUSE_WHEELUP]   = false;
  _buttonStates[GLOOST_MOUSE_WHEELDOWN] = false;


  for(unsigned int i=0; i!=_mouseDownEvents.size(); ++i)
  {
    _mouseDownEvents[i] = false;
  }

  for(unsigned int i=0; i!=_mouseUpEvents.size(); ++i)
  {
    _mouseUpEvents[i] = false;
  }
}

///////////////////////////////////////////////////////////////////////////////


  /// get the state of one of the mouse bottons

bool
Mouse::getButtonState(unsigned int buttonNum) const
{
  {
//    if(buttonNum == 5)
//        std::cout <<std::endl << "getButtonState 5" ;
    return _buttonStates.find(buttonNum)->second;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////


  /// get the state of one of the mouse bottons

void
Mouse::setButtonState(unsigned int buttonNum, bool state)
{
  {
    /// set mouseUp or mouseDown event
    if (_buttonStates[buttonNum] != state)
    {
      if (state == true)
      {
        setMouseDownEvent(buttonNum, true);
        _lastDownPos = _loc;
      }
      else
      {
        setMouseUpEvent(buttonNum, true);
        _lastUpPos = _loc;
      }
    }
    _buttonStates[buttonNum] = state;
  }
}

///////////////////////////////////////////////////////////////////////////////


  ///

bool
Mouse::getMouseDownEvent(unsigned int buttonNum) const
{
  if (buttonNum < 6)
  {
    return _mouseDownEvents.find(buttonNum)->second;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////


  ///

void
Mouse::setMouseDownEvent(unsigned int buttonNum, bool state)
{
  if (buttonNum < 6)
  {
    _mouseDownEvents[buttonNum] = state;
  }
}

///////////////////////////////////////////////////////////////////////////////


  ///

bool
Mouse::getMouseUpEvent(unsigned int buttonNum) const
{
  if (buttonNum < 6)
  {
    return _mouseUpEvents.find(buttonNum)->second;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////


  ///

void
Mouse::setMouseUpEvent(unsigned int buttonNum, bool state)
{
  if (buttonNum < 6)
  {
    _mouseUpEvents[buttonNum] = state;
  }
}


///////////////////////////////////////////////////////////////////////////////


  /// ...

//
//int
//Mouse::getAndReduceMouseWheelOffset()
//{
//
//    int offset = mouseWheelOffset;
//
//
//    if(mouseWheelOffset>0)
//      --mouseWheelOffset;
//      else if(mouseWheel < 0)
//       ++mouseWheelOffset;
//
// return offset;
//}
//
//
//int
//Mouse::getMouseWheelOffset()
//{
//  return mouseWheelOffset;
//}
///////////////////////////////////////////////////////////////////////////////





} // namespace gloost


