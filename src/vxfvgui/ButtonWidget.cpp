
/// vxfv system includes
#include <vxfvgui/ButtonWidget.h>
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

ButtonWidget::ButtonWidget(VxfvGui* gui):
    VxfvWidget(gui),
    _texcoords(),
    _value(false)
{

	_texcoords = gloost::vec4(10.0, 155.0,  46.0, 177.0);

	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_POSITIONS);
	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_TEXCOORDS);


	_scale = gloost::Vector3(20, _texcoords.a-_texcoords.g, 1.0 );

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

ButtonWidget::~ButtonWidget()
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
ButtonWidget::onInitWidget()
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
ButtonWidget::onEnterFrame()
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
ButtonWidget::onExitFrame()
{


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseEnterEvent()
{
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseLeaveEvent()
{
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseDownEvent()
{
  if (_window && _window->_isActive)
  {
    _value = true;
    onUpdateMesh();
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseUpEvent()
{
  _value = false;
  onUpdateMesh();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseDownOutsideEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseUpOutsideEvent()
{
  _value = false;
  onUpdateMesh();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseWithin()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
ButtonWidget::onMouseOutside()
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
ButtonWidget::onDraw()
{


  float borderWidth  = 7;
  float height       = 22;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
    glPushMatrix();
    {
      glTranslated((int)_position[0],
                   (int)_position[1],
                   (int)_position[2]);

      _vbo->bind();
      _vbo->draw();
      _vbo->disable();


      gloost::FreeTypeWriter* writer = _gui->getScreenWriter(VXFV_VXFVGUI_WRITER_BUTTONS);

      writer->beginText();
      {
        glColor4f(0.0,0.0,0.0, 1.0);
        writer->writeLine((int)borderWidth,
                          (int) (_scale[1] - (writer->getFontTileSet()->getTileHeight()+height)/2 + 2),
                         _title);
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
ButtonWidget::onUpdateMesh()
{

  float borderWidth  = 7;
  float height       = 22;
  float atlasSize    = 512;


  gloost::FreeTypeWriter* writer = _gui->getScreenWriter(VXFV_VXFVGUI_WRITER_BUTTONS);

  if (_scale[0] < writer->getLineLength(_title))
  {
    _scale[0] = writer->getLineLength(_title) + 2*borderWidth;
  }

  _mesh->clear();

  _vbo->dropReference();
  _vbo = new gloost::Vbo(_mesh);
  _vbo->takeReference();


  gloost::vec2 texMin(_texcoords.r+_value*36, _texcoords.g);
  gloost::vec2 texMax(_texcoords.b+_value*36, _texcoords.a);


  // build mesh


  // left corner
	pushQuad( 0.0,
            0.0,
            _position[2],
            borderWidth, height, 1.0,
            (texMin.u)/atlasSize, (texMax.v)/atlasSize,
            (borderWidth)/atlasSize, (-height)/atlasSize,
            _mesh);


  // right corner
	pushQuad( _scale[0] - borderWidth*1,
            _scale[1]-height,
            _position[2],
            borderWidth, height, 1.0,
            (texMax.u-borderWidth)/atlasSize, (texMax.v)/atlasSize,
            (borderWidth)/atlasSize, (-height)/atlasSize,
            _mesh);



  // between
	pushQuad( borderWidth,
            _scale[1] - height,
            _position[2],
            _scale[0] - borderWidth*2, height, 1.0,
            (texMin.u+borderWidth)/atlasSize, (texMax.v)/atlasSize,
            (borderWidth)/atlasSize, (-height)/atlasSize,
            _mesh);
}


////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


