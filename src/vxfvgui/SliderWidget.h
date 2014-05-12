

#ifndef H_VXFV_SLIDERWIDGET
#define H_VXFV_SLIDERWIDGET



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

class SliderWidget: public VxfvWidget
{
	public:

    // class constructor
    SliderWidget(VxfvGui* gui,
                 float minValue     = 0.0,
                 float maxValue     = 1.0,
                 float defaultValue = 0.0,
                 float resolution   = 0.01,
                 int   length       = 60 );

    // class destructor
	  virtual ~SliderWidget();


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


    // adds a snap value
    void addSnapValue(float value);


    gloost::vec4 _texcoords;
    gloost::vec4 _knobTexcoords;



    bool  _drag;

    float _value;
    float _defaultValue;

	  float _minValue;
	  float _maxValue;
	  float _resolution;

    float _normValue;

	protected:

    // container of values, the slider will snapp to while draging
    std::vector<float> _snapValues;
    float              _draggingStartPosX;
    float              _draggingStartValue;

    gloost::Mesh*      _sliderKnobMesh;
    gloost::Vbo*       _sliderKnobVbo;


};


} // namespace gloost


#endif // H_VXFV_SLIDERWIDGET


