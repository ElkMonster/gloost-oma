

#ifndef H_VXFV_VXFVWIDGET
#define H_VXFV_VXFVWIDGET



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <list>



namespace gloost
{

  class VxfvGui;
  class WindowWidget;
  class Mesh;
  class Vbo;
  class Mouse;



  //  Base class for all Widgets used by the gui

class VxfvWidget
{
	public:

    // class constructor
    VxfvWidget(VxfvGui* gui);

    // class destructor
	  virtual ~VxfvWidget();


    virtual void onInitWidget(){};
    virtual void onUpdateMesh(){};

    virtual void onEnterFrame(){};
    virtual void onExitFrame(){};

    virtual void onHandleMouse(gloost::Mouse* mouse);

    virtual void onDraw(){};


    // HANDLER FOR MOUSE STATES AND EVENTS
    virtual void onMouseEnterEvent();
    virtual void onMouseLeaveEvent();
    virtual void onMouseDownEvent();
    virtual void onMouseUpEvent();
    virtual void onMouseDownOutsideEvent();
    virtual void onMouseUpOutsideEvent();
    virtual void onMouseWithin();
    virtual void onMouseOutside();

    // HANDLER FOR KEY EVENTS
    virtual bool onHandleKey(unsigned char key, bool state);


//    virtual void onMove(float speedX, float speedY){};


    virtual void onDisable(){};
    virtual void onEnable(){};

    virtual void onHide(){};
    virtual void onUnhide(){};



    // returs true if point is within the widget
    bool inside(const gloost::Point3& location);



    // adds a quad to a mesh
    static void pushQuad( float x, float y, float z,
                          float scaleX, float scaleY, float scaleZ,
                          float texMinX, float texMinY,
                          float texScaleX, float texScaleY,
                          gloost::Mesh* mesh);

    // adds a quad to a mesh
    static void pushQuadCenter( float x, float y, float z,
                                float scaleX, float scaleY, float scaleZ,
                                float texMinX, float texMinY,
                                float texScaleX, float texScaleY,
                                gloost::Mesh* mesh);




    gloost::Point3  _position;
    gloost::Vector3 _scale;
    std::string     _title;
    std::string     _tooltipText;
    WindowWidget*   _window;


    int  _mouseWithin;
    bool _mouseEnterEvent;
    bool _mouseLeaveEvent;

    bool _mouseDownEvent;
    bool _mouseUpEvent;
    bool _mouseDownsOutsideEvent;
    bool _mouseUpOutsideEvent;

    bool _drag;



  protected:
    gloost::Mesh* _mesh;
    gloost::Vbo*  _vbo;


	protected:

    VxfvGui* _gui;




};


} // namespace gloost


#endif // H_VXFV_VXFVWIDGET


