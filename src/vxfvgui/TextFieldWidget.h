

#ifndef H_VXFV_TEXTFIELDWIDGET
#define H_VXFV_TEXTFIELDWIDGET



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

class TextFieldWidget: public VxfvWidget
{
	public:

    // class constructor
    TextFieldWidget(VxfvGui* gui);

    // class destructor
	  virtual ~TextFieldWidget();


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


    virtual bool onHandleKey(unsigned char key, bool state);


    virtual void onDraw();

//    gloost::vec4 _texcoords;


    std::string _value;
    std::string _viewValue;

    bool _editing;


	private:


};


} // namespace gloost


#endif // H_VXFV_TEXTFIELDWIDGET


