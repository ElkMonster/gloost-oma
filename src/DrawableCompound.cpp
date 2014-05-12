
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



/// gloost system includes
#include <DrawableCompound.h>
#include <Mesh.h>
#include <Vbo.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   DrawableCompound

  \brief   Compound containing a Mesh and a Vbo to use them together

  \author  Felix Weiszig
  \date    June 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

DrawableCompound::DrawableCompound():
    _mesh(new gloost::Mesh()),
    _vbo(new gloost::Vbo(_mesh)),
    _meshDirty(true)
{
	_mesh->takeReference();
	_vbo->takeReference();
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

DrawableCompound::DrawableCompound(Mesh* mesh):
    _mesh(mesh),
    _vbo(new gloost::Vbo(_mesh)),
    _meshDirty(true)
{
	_mesh->takeReference();
	_vbo->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

DrawableCompound::~DrawableCompound()
{
	_mesh->dropReference();
	_vbo->dropReference();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the Mesh dirty to indicate a change within its content and trigger an Vbo update
  \param   ...
  \remarks ...
*/

void
DrawableCompound::setMeshDirty(bool value)
{
	_meshDirty = value;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   updates the vbo, necessary if Mesh was changed
  \param   ...
  \remarks ...
*/

void
DrawableCompound::updateVbo()
{
	if (_meshDirty)
	{
	  unsigned drawMode = _vbo->getDrawMode();
    _vbo->dropReference();
    _vbo = new gloost::Vbo(_mesh);
    _vbo->takeReference();
    _vbo->setDrawMode(drawMode);
    _meshDirty = false;
	}
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   clears the Mesh and removes resources from GPU
  \param   ...
  \remarks ...
*/

void
DrawableCompound::clear()
{
	_mesh->dropReference();
	_mesh = new gloost::Mesh();
	setMeshDirty(true);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   replaces the current Mesh with another one
  \param   ...
  \remarks ...
*/

void
DrawableCompound::setMesh(Mesh* mesh)
{
  gloost::Mesh* tmpMesh = _mesh;

  _mesh = mesh;
  mesh->takeReference();

	tmpMesh->dropReference();

	setMeshDirty(true);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the Mesh
  \param   ...
  \remarks ...
*/

Mesh*
DrawableCompound::getMesh()
{
	return _mesh;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the Vbo
  \param   ...
  \remarks ...
*/

Vbo*
DrawableCompound::getVbo()
{
	return _vbo;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   draws the compound
  \param   ...
  \remarks ...
*/

void
DrawableCompound::draw()
{
  _vbo->bind();
	_vbo->draw();
	_vbo->disable();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   draws the compound
  \param   ...
  \remarks ...
*/

void
DrawableCompound::updateAndDraw()
{
	updateVbo();
//	std::cerr << std::endl << "_vbo->getMesh()->getNumInterleavedPackages(): " << _vbo->getMesh()->getNumInterleavedPackages();
  _vbo->bind();
	_vbo->draw();
	_vbo->disable();
}


////////////////////////////////////////////////////////////////////////////////





} // namespace gloost



