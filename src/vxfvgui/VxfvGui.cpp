
/// vxfv system includes
#include <vxfvgui/VxfvGui.h>
#include <vxfvgui/VxfvWidget.h>
#include <vxfvgui/WindowWidget.h>


// gloost includes
#include <TextureManager.h>
#include <Mouse.h>
#include <FreeTypeWriter.h>


/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   VxfvGui

  \brief   VxfvGui handles VxfvWidgets

  \author  Felix Weiszig
  \date    May 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

VxfvGui::VxfvGui(const std::string& dataFolderPath):
    _atlasTextureId(0),
    _guiTime(0),
    _disabled(false),
    _dataFolderPath(dataFolderPath),
    _widgetsById(),
    _widgetIdCounter(0),
    _windows(),
    _windowDrawList(),
    _guiWasUsed(false),
    _mouse(new gloost::Mouse()),
    _screenWriters()
{

  std::cerr << std::endl << "Message from gloost::VxfvGui(const std::string& dataFolderPath): ";
  std::cerr << std::endl << "Vxfv gui is in alpha phase. Please use it with caution...";
  std::cerr << std::endl;
  std::cerr << std::endl;

//  std::cerr << std::endl << "VxfvGui::VxfvGui(const std::string& dataFolderPath): " << this;


//  _widgetsById.resize(1, 0);



  // window border text
  _screenWriters.push_back(new gloost::FreeTypeWriter(dataFolderPath + "/fonts/arial.ttf", 10, true));
//
//  // button text
  _screenWriters.push_back(new gloost::FreeTypeWriter(dataFolderPath + "/fonts/arial.ttf", 9, false));
//
//  // small value text
  _screenWriters.push_back(new gloost::FreeTypeWriter(dataFolderPath + "/fonts/arial.ttf", 8, false));


	_atlasTextureId = gloost::TextureManager::getInstance()->createTexture(dataFolderPath + "/gui/widgets_atlas.png");
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

VxfvGui::~VxfvGui()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Inits the VxfvGui
  \param   ...
  \remarks ...
*/

void
VxfvGui::init()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   process events
  \param   ...
  \remarks ...
*/

void
VxfvGui::frameStep()
{

  if (!_mouse->getButtonState(GLOOST_MOUSE_BUTTON1))
  {
    _guiWasUsed = false;
  }

  if (!_disabled)
  {
    // determine active window
    if (_mouse->getMouseDownEvent(GLOOST_MOUSE_BUTTON1) && _windowDrawList.size())
    {
      // this is the window in the front and the only one that could be active at the moment
      WindowWidget* upperWindow = (*(--_windowDrawList.end()));

      // has a mouseDown event occured outside the current upper window...
      if ( !upperWindow->inside(_mouse->getLoc()) || !upperWindow->_isActive )
      {
        upperWindow->_isActive = false;
        upperWindow->onUpdateMesh();

        WindowListIterator windowIt    = _windowDrawList.begin();
        WindowListIterator windowEndIt = _windowDrawList.end();

        WindowListIterator newUpperWindowIt = _windowDrawList.end();

        for (; windowIt!=windowEndIt; ++windowIt)
        {
          if ((*windowIt)->inside(_mouse->getLoc()) )
          {
            newUpperWindowIt = windowIt;
          }
        }

        // activate new active window and bring it to the front (== end of the draw list)
        if (newUpperWindowIt != _windowDrawList.end())
        {
          WindowWidget* newUpperWindow = (*newUpperWindowIt);
          newUpperWindow->_isActive = true;
          upperWindow->onUpdateMesh();

          _windowDrawList.erase(newUpperWindowIt);
          _windowDrawList.push_back(newUpperWindow);

        }
      }
    }


    WindowListIterator windowIt    = _windowDrawList.begin();
    WindowListIterator windowEndIt = _windowDrawList.end();

    for (; windowIt!=windowEndIt; ++windowIt)
    {
      if ((*windowIt)->inside(_mouse->getLoc()) )
      {
        _guiWasUsed = true;
      }
    }


    // call handle mouse on all windows
    {
      WindowMapIterator windowsIt    = _windows.begin();
      WindowMapIterator windowsEndIt = _windows.end();

      for (; windowsIt!=windowsEndIt; ++windowsIt)
      {
        windowsIt->second->onHandleMouse(_mouse);
      }
    }
  }

  // send onEnterFrame event to all windows/widgets
  {
    WindowMapIterator windowsIt    = _windows.begin();
    WindowMapIterator windowsEndIt = _windows.end();

    for (; windowsIt!=windowsEndIt; ++windowsIt)
    {
      windowsIt->second->onEnterFrame();
    }
  }

  // send onExitFrame event to all windows/widgets
  {
    WindowMapIterator windowsIt    = _windows.begin();
    WindowMapIterator windowsEndIt = _windows.end();

    for (; windowsIt!=windowsEndIt; ++windowsIt)
    {
      windowsIt->second->onExitFrame();
    }
  }
  _mouse->resetMouseEvents();
  _mouse->setSpeedToZero();

  ++_guiTime;

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   mouse motion callback
  \param   ...
  \remarks ...
*/

void
VxfvGui::mouseMotionFunc(int mouse_h, int screenHeightMinusMouse_v)
{
  _mouse->setLoc(mouse_h, screenHeightMinusMouse_v);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   mouse callback
  \param   ...
  \remarks ...
*/

void
VxfvGui::mouseFunc(int button, int state, int mouse_h, int screenHeightMinusMouse_v)
{
  _mouse->setButtonState(button+1, !state);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   key press callback
  \param   ...
  \remarks ...
*/

bool
VxfvGui::keyFunc(unsigned char key, bool state)
{
  std::map<unsigned, VxfvWidget*>::iterator widgetIt = _widgetsById.begin();
  std::map<unsigned, VxfvWidget*>::iterator endIt    = _widgetsById.end();

  bool received = false;

  for(; widgetIt != endIt; ++widgetIt)
  {
    received = received || (*widgetIt).second->onHandleKey(key, state);
  }

  return received;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   draw gui
  \param   ...
  \remarks ...
*/

void
VxfvGui::draw()
{

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);
  //  glDepthFunc(GL_LEQUAL);


    gloost::Texture* atlas = gloost::TextureManager::getInstance()->getTextureWithoutRefcount(_atlasTextureId);
    atlas->bind();


    // draw all windows
    WindowListIterator windowIt    = _windowDrawList.begin();
    WindowListIterator windowEndIt = _windowDrawList.end();

    for (; windowIt!=windowEndIt; ++windowIt)
    {
      (*windowIt)->onDraw();
    }

    atlas->unbind();

  }
  glPopAttrib();

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Window widget
  \param   ...
  \remarks ...
*/

WindowWidget*
VxfvGui::createWindow(const std::string& name)
{
	WindowWidget* newWindow = new WindowWidget(this);
	newWindow->_title = name;
	_windows[name] = newWindow;
	_windowDrawList.push_back(newWindow);
	return newWindow;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   adds a Window widget or a derivative to the gui
  \param   ...
  \remarks ...
*/

WindowWidget*
VxfvGui::addWindow(const std::string& name, WindowWidget* window)
{
	window->_title = name;
	_windows[name] = window;
	_windowDrawList.push_back(window);
	return window;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a window widget for a name
  \param   ...
  \remarks ...
*/

WindowWidget*
VxfvGui::getWindow(const std::string& name)
{
	std::map<std::string, WindowWidget*>::iterator pos = _windows.find(name);

	if (pos == _windows.end())
	{
	  std::cerr << std::endl << "ERROR in VxfvGui::getWindow(const std::string& name): ";
	  std::cerr << std::endl << "         Could NOT find Window with name " << name;
	  std::cerr << std::endl;
	  return 0;
	}

	return pos->second;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the gloost::Mouse used by the Gui
  \param   ...
  \remarks ...
*/

const gloost::Mouse*
VxfvGui::getMouse() const
{
  return _mouse;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the gloost::Mouse used by the Gui
  \param   ...
  \remarks ...
*/

gloost::Mouse*
VxfvGui::getMouse()
{
  return _mouse;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a screen writer
  \param   ...
  \remarks ...
*/

gloost::FreeTypeWriter*
VxfvGui::getScreenWriter(unsigned id)
{
  return _screenWriters[id];
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   registers a widget and returns an id to reference it
  \param   ...
  \remarks ...
*/

unsigned
VxfvGui::registerWidget(VxfvWidget* widget)
{

  _widgetsById[_widgetIdCounter] = widget;

  unsigned id = _widgetIdCounter;
  ++_widgetIdCounter;

  return id;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns true is mouse was handled by the gui
  \param   ...
  \remarks ...
*/

bool
VxfvGui::wasGuiUsed()
{
  return _guiWasUsed;
}

////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


