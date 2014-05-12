
/// vxfv system includes
#include <vxfvgui/VxfvWidget.h>
#include <vxfvgui/WindowWidget.h>
#include <vxfvgui/VxfvGui.h>


// gloost includes
#include <Mesh.h>
#include <Vbo.h>
#include <Mouse.h>


/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   VxfvWidget

  \brief   Base class for all Widgets used by the gui

  \author  Felix Weiszig
  \date    May 2011
  \remarks ..
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

VxfvWidget::VxfvWidget(VxfvGui* gui):
    _position(),
    _scale(),
    _title("none"),
    _tooltipText("none"),
    _window(0),
    _gui(gui),
    _mouseWithin(false),
    _mouseEnterEvent(false),
    _mouseLeaveEvent(false),
    _mouseDownEvent(false),
    _mouseUpEvent(false),
    _mouseDownsOutsideEvent(false),
    _mouseUpOutsideEvent(false),
    _drag(0),
    _mesh(new gloost::Mesh()),
    _vbo(new gloost::Vbo(_mesh))
{
	_mesh->takeReference();
	_vbo->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

VxfvWidget::~VxfvWidget()
{
	_mesh->dropReference();
	_vbo->dropReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

void
VxfvWidget::onHandleMouse(gloost::Mouse* mouse)
{

  // add window position to current mouse position
  gloost::Point3 mousePos = mouse->getLoc();
  if (_window)
  {
    mousePos -= _window->_position;
  }

  bool within = inside(mousePos);

  // mouse enter
  if (within && !_mouseWithin)
  {
    _mouseEnterEvent = true;
  }
  else
  {
    _mouseEnterEvent = false;
  }


  // mouse leave
  if (!within && _mouseWithin)
  {
    _mouseLeaveEvent = true;
  }
  else
  {
    _mouseLeaveEvent = false;
  }


  // mouse down on this widget
  if (within && mouse->getMouseDownEvent(GLOOST_MOUSE_BUTTON1))
  {
    _mouseDownEvent = true;
  }
  else
  {
    _mouseDownEvent = false;
  }


  // mouse up on this widget
  if (within && mouse->getMouseUpEvent(GLOOST_MOUSE_BUTTON1))
  {
    _mouseUpEvent = true;
  }
  else
  {
    _mouseUpEvent = false;
  }


  // mouse down OUTSIDE on this widget
  if (!within && mouse->getMouseDownEvent(GLOOST_MOUSE_BUTTON1))
  {
    _mouseDownsOutsideEvent = true;
  }
  else
  {
    _mouseDownsOutsideEvent = false;
  }


  // mouse up OUTSIDE on this widget
  if (!within && mouse->getMouseUpEvent(GLOOST_MOUSE_BUTTON1))
  {
    _mouseUpOutsideEvent = true;
  }
  else
  {
    _mouseUpOutsideEvent = false;
  }


  // finally set mouseWithin
  if (within)
  {
    _mouseWithin += within;
  }
  else
  {
    _mouseWithin = false;
  }



  // call handler for events
  if (_mouseDownEvent)
  {
    onMouseDownEvent();
  }

  if (_mouseUpEvent)
  {
    onMouseUpEvent();
  }

  if (_mouseDownsOutsideEvent)
  {
    onMouseDownOutsideEvent();
  }

  if (_mouseUpOutsideEvent)
  {
    onMouseUpOutsideEvent();
  }

  if (_mouseWithin)
  {
    onMouseWithin();
  }
  else
  {
    onMouseOutside();
  }


  if (_mouseEnterEvent)
  {
    onMouseEnterEvent();
  }

  if (_mouseLeaveEvent)
  {
    onMouseLeaveEvent();
  }


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseEnterEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseLeaveEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseDownEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseUpEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseDownOutsideEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseUpOutsideEvent()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseWithin()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
VxfvWidget::onMouseOutside()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks Should return TRUE if the widget handled the key
*/

/*virtual */
bool
VxfvWidget::onHandleKey(unsigned char key, bool state)
{
  return false;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

bool
VxfvWidget::inside(const gloost::Point3& location)
{
	if (   location[0] > _position[0] && location[0] < _position[0] +_scale[0]
      && location[1] > _position[1] && location[1] < _position[1] +_scale[1])
  {
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   adds a quad to a mesh
  \param   ...
  \remarks ...
*/

void
VxfvWidget::pushQuad( float x, float y, float z,
                      float scaleX, float scaleY, float scaleZ,
                      float texMinX, float texMinY,
                      float texScaleX, float texScaleY,
                      gloost::Mesh* mesh)
{

	std::vector<float>&            attribs = mesh->getInterleavedAttributes();
	std::vector<gloost::QuadFace>& quads   = mesh->getQuads();

  mesh->pushInterleavedComponent(gloost::Vector3(x, y, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY));

  mesh->pushInterleavedComponent(gloost::Vector3(x + scaleX, y, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY));

  mesh->pushInterleavedComponent(gloost::Vector3(x + scaleX, y+scaleY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY+texScaleY));

  mesh->pushInterleavedComponent(gloost::Vector3(x, y+scaleY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY+texScaleY));


  unsigned index = quads.size()*4;

  quads.push_back(gloost::QuadFace(index,index+1,index+2,index+3));
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   adds a centered quad to a mesh
  \param   ...
  \remarks ...
*/

void
VxfvWidget::pushQuadCenter( float x, float y, float z,
                            float scaleX, float scaleY, float scaleZ,
                            float texMinX, float texMinY,
                            float texScaleX, float texScaleY,
                            gloost::Mesh* mesh)
{

  float scaleHalfX = scaleX*0.5;
  float scaleHalfY = scaleY*0.5;
//  float scaleHalfZ -= scaleZ*0.5;


	std::vector<float>&            attribs = mesh->getInterleavedAttributes();
	std::vector<gloost::QuadFace>& quads   = mesh->getQuads();

  mesh->pushInterleavedComponent(gloost::Vector3(x-scaleHalfX, y-scaleHalfY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY));

  mesh->pushInterleavedComponent(gloost::Vector3(x + scaleHalfX, y-scaleHalfY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY));

  mesh->pushInterleavedComponent(gloost::Vector3(x + scaleHalfX, y+scaleHalfY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY+texScaleY));

  mesh->pushInterleavedComponent(gloost::Vector3(x - scaleHalfX, y+scaleHalfY, z));
  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY+texScaleY));


  unsigned index = quads.size()*4;

  quads.push_back(gloost::QuadFace(index,index+1,index+2,index+3));
}

////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


