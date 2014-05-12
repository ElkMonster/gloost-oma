

#ifndef H_VXFV_WINDOWBORDERWIDGET
#define H_VXFV_WINDOWBORDERWIDGET



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

class WindowBorderWidget: public VxfvWidget
{
	public:

    // class constructor
    WindowBorderWidget(VxfvGui* gui);

    // class destructor
	  virtual ~WindowBorderWidget();


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


	private:

   bool _windowMinimized;



};


} // namespace gloost


#endif // H_VXFV_WINDOWBORDERWIDGET


