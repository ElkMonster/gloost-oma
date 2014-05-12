
/// vxfv system includes
#include <vxfvgui/TextFieldWidget.h>
#include <vxfvgui/WindowWidget.h>
#include <vxfvgui/VxfvGui.h>

// gloost includes
#include <gloostConfig.h>
#include <gloostRenderGoodies.h>
#include <Mesh.h>
#include <Vbo.h>
#include <Mouse.h>
#include <FreeTypeWriter.h>
#include <TextureManager.h>
#include <TileSet.h>

/// cpp includes
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <algorithm>



namespace gloost
{

/**
  \class   VxfvWidget

  \brief   A button widget

  \author  Felix Weiszig
  \date    May 2011
  \remarks ..
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

TextFieldWidget::TextFieldWidget(VxfvGui* gui):
    VxfvWidget(gui),
//    _texcoords(),
    _value(""),
    _viewValue(""),
    _editing(false)
{

//	_texcoords = gloost::vec4(10.0, 155.0,  46.0, 177.0);

	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_POSITIONS);
//	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_TEXCOORDS);


//	_scale = gloost::Vector3(20, _texcoords.a-_texcoords.g, 1.0 );

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

TextFieldWidget::~TextFieldWidget()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TextFieldWidget::onInitWidget()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TextFieldWidget::onEnterFrame()
{


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TextFieldWidget::onExitFrame()
{


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseEnterEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseLeaveEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseDownEvent()
{
  if (_window && _window->_isActive)
  {
    _editing = true;
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseUpEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseDownOutsideEvent()
{
  _editing = false;
//  _value = _viewValue;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseUpOutsideEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseWithin()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TextFieldWidget::onMouseOutside()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks Should return TRUE if the widget handled the key
*/

/*virtual */
bool
TextFieldWidget::onHandleKey(unsigned char key, bool state)
{

  std::cerr << std::endl << "key: " << (int)key;

  if (_editing)
  {
    if (key == 8 && _value.length())
    {
      _value = _value.substr(0, _value.length()-1);
    }
    else if (key == 13)
    {
      _editing = false;
    }
    else if (key >= 32 && key <= 127)
    {
      _value = _value + gloost::toString(key);
    }
  }

  return false;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TextFieldWidget::onDraw()
{


  float borderWidth  = 7;
  float height       = 22;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
    glPushMatrix();
    {
      gloost::FreeTypeWriter* writer = _gui->getScreenWriter(VXFV_VXFVGUI_WRITER_BUTTONS);
      int titleLength = writer->getLineLength(_title);


      glTranslated((int)_position[0]+titleLength,
                   (int)_position[1],
                   (int)_position[2]);

      glDisable(GL_TEXTURE_2D);
      glEnable(GL_COLOR_MATERIAL);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0);

      _vbo->bind();
      _vbo->draw();
      _vbo->disable();

      std::string cursorString = "";

      if (_editing)
      {
        cursorString = "|";
      }


      writer->beginText();
      {
        glColor4f(0.0,0.0,0.0, 1.0);
        writer->writeLine(-titleLength,
                          0.0,
                         _title);

        writer->writeLine(0.0,
                          0.0,
                         _value + cursorString);


        writer->writeLine(_value + cursorString);
      }
      writer->endText();

      gloost::TextureManager::getInstance()->getTextureWithoutRefcount(_gui->_atlasTextureId)->bind();
      glColor4f(1.0,1.0,1.0, 1.0);

    }
    glPopMatrix();


	}
  glPopAttrib();

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TextFieldWidget::onUpdateMesh()
{

  gloost::FreeTypeWriter* writer = _gui->getScreenWriter(VXFV_VXFVGUI_WRITER_BUTTONS);

  int titleHeight = writer->getFontTileSet()->getTileHeight();

  _scale[1] = titleHeight;

  _mesh->clear();

  _vbo->dropReference();
  _vbo = new gloost::Vbo(_mesh);
  _vbo->takeReference();


  // build mesh
  _mesh->pushInterleavedComponent(gloost::Vector3(0.0, 0.0, 0.0));
//  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY));

  _mesh->pushInterleavedComponent(gloost::Vector3(_scale[0], 0.0, 0.0));
//  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY));

  _mesh->pushInterleavedComponent(gloost::Vector3(_scale[0], _scale[1], 0.0));
//  mesh->pushInterleavedComponent(gloost::vec2(texMinX+texScaleX, texMinY+texScaleY));

  _mesh->pushInterleavedComponent(gloost::Vector3(0.0, _scale[1], 0.0));
//  mesh->pushInterleavedComponent(gloost::vec2(texMinX, texMinY+texScaleY));


  _mesh->getQuads().push_back(gloost::QuadFace(0,1,2,3));
}


////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


