

#ifndef H_VXFV_WINDOWWIDGET
#define H_VXFV_WINDOWWIDGET



/// vxfv includes
#include <vxfvgui/VxfvWidget.h>


/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <list>
#include <map>



namespace gloost
{

  class Mouse;

  //  Base class for all Widgets used by the gui

class WindowWidget: public VxfvWidget
{
	public:


	  typedef std::list<VxfvWidget*>           WidgetList;
	  typedef std::list<VxfvWidget*>::iterator WidgetListIterator;


    // class constructor
    WindowWidget(VxfvGui* gui);

    // class destructor
	  virtual ~WindowWidget();


	  // adds a child widget
	  unsigned addWidget(VxfvWidget* widget, const std::string& name = "");
	  // removes a child widget
	  void removeWidget(VxfvWidget* widget);


	  // returns a Widget for a name or 0
    VxfvWidget* getWidget(const std::string& name);


	  // returns a reference to the list of widgets of this window
    WidgetList& getWidgetList();

	  // returns a const reference to the list of widgets of this window
    const WidgetList& getWidgetList() const;



    virtual void onHandleMouse(gloost::Mouse* mouse);


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



    gloost::vec4 _backgroundColor;

    gloost::vec4 _texcoords;


    bool _isActive;
    bool _minimized;


	private:

    std::list<VxfvWidget*>             _widgets;
    std::map<std::string, VxfvWidget*> _widgetsByName;



};


} // namespace gloost


#endif // H_VXFV_WINDOWWIDGET


