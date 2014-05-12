
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

            gloost is being created by Felix Weißig and Stephan Beck

     Felix Weißig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef GLOOST_GUI_H
#define GLOOST_GUI_H


/// shows a message in the gloost::TextLog if a widget is added
// #define GLOOST_GUI_ADDWIDGET_MESSAGE_ON_TEXTLOG


/// puppets system includes
#include<gui/Widget.h>
#include<gui/Slider.h>
#include<gui/Toggle.h>
#include<gui/Button.h>
#include<gui/Pad.h>
#include<gui/PropertyInspector.h>
#include<gui/TextInput.h>
#include<gui/WidgetGroup.h>
#include<gui/Histogram.h>

/// gloost includes
#include <Mouse.h>

/// cpp includes
#include <string>
#include <map>
#include <vector>
#include <list>



namespace gloost
{


  //  Gui holding all kinds of widgets and provides mouse events to them

class Gui
{
	public:


    typedef std::list<Widget*>         WidgetList;
    typedef WidgetList::iterator       WidgetListIterator;
    typedef WidgetList::const_iterator WidgetListConstIterator;


    /// class constructor
    Gui(const std::string& dataFolderPath = "../../data/", gloost::Mouse* mouse = 0);


    /// destructor
    virtual ~Gui();



    /// processes the gui and creates mouseevents for the current mouse state,
    /// returns 1 if the mouse was inside a widget
    bool frameStep();

    /// draw this gui
    void draw();



    /// get the node wich is graphicly located below the mouse pointer
    Widget* getWidgetByMousePosition();


    /// add a Widget to find it in the tree for communication
    unsigned int addWidget(Widget* widget);



    /// set a property on all widgets
    void setPropOnAllWidgets(std::string name, float value);

    /// set a property on all widgets
    void setPropOnAllWidgets(std::string name, std::string value);



    /// move all widgets
    void moveAllWidgets(const Vector2& offset);



    /// call mouseUpOutside on all widgets
    void callMouseUpOutsideOnAllWidgets();



    /// creates unique IDs for the Nodes
    unsigned int getNewUniqueId();



    /// get a registered Widget by Id
    Widget* getWidgetById(unsigned int id);

    /// get a registered Node by Name
    Widget* getWidgetByName(const std::string&  name);


    /// get a list of type gloost::Gui
    WidgetList* getWidgets();


    /// returns the path to folder where folders with fonts and textures for the widgets are located
    const std::string& getDataFolderPath();


    /// get a pointer to the mouse
    gloost::Mouse* getMouse();


    /// call these functions to update the gui every frame if you use glut
    void glutMouseFunc(int button, int state, int mouse_h, int screenHeightMinusMouse_v);
    void glutMotionFunc(int mouse_h, int screenHeightMinusMouse_v);


    /// send a key to all widgets
    bool handleKeyDownEvent(const unsigned char& asciiChar);


    /// enable dragMode on all widgets
    void enableDragMode();

    /// disable dragMode on all widgets
    void disableDragMode();

    /// inverse dragMode on all widgets
    void toggleDragMode();


    /// writes the gui to an xml file
    bool writeGuiToXml(const std::string& filepath);


    /// returns the current active widget (last with mouseWithin)
    Widget* getCurrentActiveWidget();

    /// set current active widget
    void setCurrentActiveWidget(Widget* widget);


    /// get last id given to a widget by the gui
    unsigned int getLastWidgetId() const;


	private:

    WidgetList     _guiElements;

    gloost::Mouse* _mouse;
    bool           _mouseIsExtern;


    unsigned int _guiWidth;
    unsigned int _guiHeight;


    /// path to the theme
    std::string _dataFolderPath;



    /// unique or default name of this node
    unsigned int _idCounter;


    /// lookup for id -> Widget
    std::map<unsigned int, Widget*> _widgetsById;

    /// lookup for name -> _Widget;
    std::map<std::string, Widget*>  _widgetsByName;

    /// current active widget
    Widget* _currentActiveWidget;


    bool _enabled;



};


} // namespace gloost


#endif // GLOOST_GUI_H




