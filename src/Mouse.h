
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

            gloost is being created by Felix Weiﬂig and Stephan Beck

     Felix Weiﬂig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef GLOOST_MOUSE_H
#define GLOOST_MOUSE_H


#define GLOOST_MOUSE_BUTTON1 1
#define GLOOST_MOUSE_BUTTON2 2
#define GLOOST_MOUSE_BUTTON3 3
#define GLOOST_MOUSE_BUTTON4 4
#define GLOOST_MOUSE_BUTTON5 5
#define GLOOST_MOUSE_BUTTON6 6

#define GLOOST_MOUSE_WHEELUP   7
#define GLOOST_MOUSE_WHEELDOWN 8




/// gloost system includes
#include <Point3.h>
#include <Vector3.h>



/// cpp includes
#include <string>
#include <map>



namespace gloost
{


  ///  A Mouse, updated by the Eventhandler or manualy

class Mouse
{

	public:
    /// class constructor
    Mouse();

    /// class destructor
	  ~Mouse();



    /// get the location of the mouse
    const Point3& getLoc() const;
    void   setLoc(Point3 loc);
    void   setLoc(float x, float y, float z = 0.0);

    /// get the location of the mouse one frame before
    const Point3& getOldLoc() const;


    /// get the coordinates of the last mouseUp
    const Point3& getLastMouseDownLoc() const;

    /// get the coordinates of the last mouseUp
    const Point3& getLastMouseUpLoc() const;



    /// get the moving speed of the mouse (in pixel/frame)
    Point3 getSpeed() const;



    /// set the speed of the mouse to zero
    void setSpeedToZero();

    /// reset mouse events so they can be set in the next frame
    void resetMouseEvents();



    /// get the state of one of the mouse bottons (GLOOST_MOUSE_BUTTON1, GLOOST_MOUSE_BUTTON2, GLOOST_MOUSE_BUTTON3, ...)
    bool getButtonState(unsigned int buttonNum) const;
    void setButtonState(unsigned int buttonNum, bool state);



    bool getMouseDownEvent(unsigned int buttonNum) const;
    void setMouseDownEvent(unsigned int buttonNum, bool eventToggle);

    bool getMouseUpEvent(unsigned int buttonNum) const;
    void setMouseUpEvent(unsigned int buttonNum, bool eventToggle);

//    int getAndReduceMouseWheelOffset();


	private:


    Point3                        _loc;
    Point3                        _oldLoc;
    Vector3                       _speed;
    std::map<unsigned int, bool>  _buttonStates;
    Point3                        _lastDownPos;
    Point3                        _lastUpPos;

    std::map<unsigned int, bool> _mouseDownEvents;
    std::map<unsigned int, bool> _mouseUpEvents;

//    int mouseWheelOffset;


};


} // namespace gloost


#endif // GLOOST_MOUSE_H


