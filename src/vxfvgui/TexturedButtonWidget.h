

#ifndef H_VXFV_TEXTUREDBUTTONWIDGET
#define H_VXFV_TEXTUREDBUTTONWIDGET



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

class TexturedButtonWidget: public VxfvWidget
{
	public:

    // class constructor
    TexturedButtonWidget(VxfvGui*     gui,
                         unsigned     textureId,
                         gloost::vec4 texcoords = gloost::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                         unsigned     numStates = 3);

    // class destructor
	  virtual ~TexturedButtonWidget();


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


    unsigned     _textureId;
    gloost::vec4 _texcoords;
    unsigned     _numStates;


    bool        _value;


	private:





};


} // namespace gloost


#endif // H_VXFV_TEXTUREDBUTTONWIDGET


