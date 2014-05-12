

#ifndef H_VXFV_BUTTONWIDGET
#define H_VXFV_BUTTONWIDGET



/// vxfv includes
#include <vxfvgui/VxfvWidget.h>


/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <list>



namespace gloost
{


  class Mouse;


  //  A button widget

class ButtonWidget: public VxfvWidget
{
	public:

    // class constructor
    ButtonWidget(VxfvGui* gui);

    // class destructor
	  virtual ~ButtonWidget();


    virtual void onInitWidget();
    virtual void onUpdateMesh();

    virtual void onEnterFrame();
    virtual void onExitFrame();


    // HANDLER FOR MOUSE STATES AND EVENTS
    virtual void onMouseEnterEvent();
    virtual void onMouseLeaveEvent();
    virtual void onMouseDownEvent();
    virtual void onMouseUpEvent();
    virtual void onMouseDownOutsideEvent();
    virtual void onMouseUpOutsideEvent();
    virtual void onMouseWithin();
    virtual void onMouseOutside();


    virtual void onDraw();

    gloost::vec4 _texcoords;


    bool        _value;


	private:





};


} // namespace gloost


#endif // H_VXFV_BUTTONWIDGET


