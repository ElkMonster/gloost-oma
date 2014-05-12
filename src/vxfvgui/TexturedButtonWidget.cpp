
/// vxfv system includes
#include <vxfvgui/TexturedButtonWidget.h>
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



namespace gloost{

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

TexturedButtonWidget::TexturedButtonWidget(VxfvGui*     gui,
                                           unsigned     textureId,
                                           gloost::vec4 texcoords,
                                           unsigned     numStates):
    VxfvWidget(gui),
    _textureId(textureId),
    _texcoords(texcoords),
    _numStates(numStates),
    _value(false)
{

//	_texcoords = gloost::vec4(10.0, 155.0,  46.0, 177.0);

	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_POSITIONS);
	_mesh->setSupportedInterleavedAttribute(GLOOST_MESH_TEXCOORDS);


	_scale = gloost::Vector3(_texcoords.b-_texcoords.r,
                           _texcoords.a-_texcoords.g, 1.0 );

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

TexturedButtonWidget::~TexturedButtonWidget()
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
TexturedButtonWidget::onInitWidget()
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
TexturedButtonWidget::onEnterFrame()
{

  if (_window)
  {


  }

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \param   ...
  \remarks ...
*/

/*virtual*/
void
TexturedButtonWidget::onExitFrame()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TexturedButtonWidget::onMouseEnterEvent()
{
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TexturedButtonWidget::onMouseLeaveEvent()
{
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TexturedButtonWidget::onMouseDownEvent()
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
TexturedButtonWidget::onMouseUpEvent()
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
TexturedButtonWidget::onMouseDownOutsideEvent()
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TexturedButtonWidget::onMouseUpOutsideEvent()
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
TexturedButtonWidget::onMouseWithin()
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks ...
*/

/*virtual */
void
TexturedButtonWidget::onMouseOutside()
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
TexturedButtonWidget::onDraw()
{

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
    glPushMatrix();
    {
      glColor4d(1.0,1.0,1.0,1.0);

      glTranslated((int)_position[0],
                   (int)_position[1],
                   (int)_position[2]);

      _vbo->bind();
      _vbo->draw();
      _vbo->disable();


//      gloost::FreeTypeWriter* writer = _gui->getScreenWriter(VXFV_VXFVGUI_WRITER_BUTTONS);
//
//      writer->beginText();
//      {
//        glColor4f(0.0,0.0,0.0, 1.0);
//        writer->writeLine((int)borderWidth,
//                          (int) (_scale[1] - (writer->getFontTileSet()->getTileHeight()+height)/2 + 2),
//                         _title);
//      }
//      writer->endText();

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
TexturedButtonWidget::onUpdateMesh()
{

  float borderWidth  = 7;
  float height       = 22;
  float atlasSize    = 512;


  _mesh->clear();

  _vbo->dropReference();
  _vbo = new gloost::Vbo(_mesh);
  _vbo->takeReference();


  // left corner
  gloost::vec2 texMin(_texcoords.r+_value*_scale[0], _texcoords.g);
  gloost::vec2 texMax(_texcoords.b+_value*_scale[0], _texcoords.a);


  // build mesh
	pushQuad( 0.0,
            0.0,
            _position[2],
            _scale[0], _scale[1], 1.0,
            (texMin.u)/atlasSize, (texMax.v)/atlasSize,
            (_scale[0])/atlasSize, (-_scale[1])/atlasSize,
            _mesh);
}


////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


