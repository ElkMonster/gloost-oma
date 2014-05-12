

#ifndef H_VXFV_TOGGLEWIDGET
#define H_VXFV_TOGGLEWIDGET



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

  //  Base class for all Widgets used by the gui

class ToggleWidget: public VxfvWidget
{
	public:

    // class constructor
    ToggleWidget(VxfvGui* gui, bool defaultValue = false);

    // class destructor
	  virtual ~ToggleWidget();


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

    bool _value;


	protected:

	  bool _defaultValue;




};


} // namespace gloost


#endif // H_VXFV_TOGGLEWIDGET


