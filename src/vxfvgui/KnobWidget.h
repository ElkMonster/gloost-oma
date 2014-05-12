

#ifndef H_VXFV_KNOBWIDGET
#define H_VXFV_KNOBWIDGET



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

class KnobWidget: public VxfvWidget
{
	public:

    // class constructor
    KnobWidget(VxfvGui* gui,
               float minValue = 0.0,
               float maxValue = 1.0,
               float defaultValue = 0.0,
               float resolution = 0.01 );

    // class destructor
	  virtual ~KnobWidget();


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

    virtual void onValueChange();


    gloost::vec4 _texcoords;



    bool  _drag;

    float _value;
    float _defaultValue;

	  float _minValue;
	  float _maxValue;
	  float _resolution;

    float _normValue;

	protected:




};


} // namespace vxfv


#endif // H_VXFV_KNOBWIDGET


