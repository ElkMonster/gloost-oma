
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
#include <experimental/VertexAttribContainer.h>
#include <Mesh.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   VertexAttribContainer

  \brief   ...

  \author  Felix Weiszig, Henning Gruendl
  \date    November 2011
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

VertexAttribContainer::VertexAttribContainer():
    SharedResource(),
    _interleavedAttributes(),
    _interleavedAttribInfo()
{
	// insert your code here
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

VertexAttribContainer::VertexAttribContainer(Mesh* mesh):
    SharedResource(),
    _interleavedAttributes(),
    _interleavedAttribInfo()
{
  Mesh* interleavedMesh = new gloost::Mesh(mesh, true);
  interleavedMesh->takeReference();

  if (interleavedMesh->getInterleavedAttributes().size())
  {
    if (interleavedMesh->isInterleavedAttributeSupported(GLOOST_MESH_POSITIONS))
    {
      addInterleavedAttrib(3, 12, "inPosition");
    }
    if (interleavedMesh->isInterleavedAttributeSupported(GLOOST_MESH_NORMALS))
    {
      addInterleavedAttrib(3, 12, "inNormal");
    }
    if (interleavedMesh->isInterleavedAttributeSupported(GLOOST_MESH_COLORS))
    {
      addInterleavedAttrib(4, 16, "inColor");
    }
    if (interleavedMesh->isInterleavedAttributeSupported(GLOOST_MESH_TEXCOORDS))
    {
      addInterleavedAttrib(2, 8, "inTexcoord");
    }
    _interleavedAttributes = interleavedMesh->getInterleavedAttributes();
  }

  interleavedMesh->dropReference();

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

VertexAttribContainer::~VertexAttribContainer()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   adds a info for an interleaved attrib
  \param   ...
  \remarks ...
*/

void
VertexAttribContainer::addInterleavedAttrib(unsigned numElements,
                                            unsigned stride,
                                            const    std::string& name)
{
	_interleavedAttribInfo.push_back(AttribInfo(numElements, stride, name));
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the vector of interleaved attributes
  \remarks ...
*/

std::vector<float>&
VertexAttribContainer::getInterleavedAttributes()
{
  return _interleavedAttributes;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the vector of information for each attrib within the interleaved structure
  \remarks ...
*/

std::vector<VertexAttribContainer::AttribInfo>&
VertexAttribContainer::getInterleavedAttribInfo()
{
  return _interleavedAttribInfo;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief returns the layout of this Attributes to be used in the vertex shader
  \remarks ...
*/

std::string
VertexAttribContainer::getLayoutString() const
{
  std::string layoutString = "\n// vertex attribute layout \n";

//layout(location=0) in vec3 in_position;
//layout(location=1) in vec3 in_normal;
//layout(location=2) in vec4 in_color;

  for (unsigned int i=0; i!=_interleavedAttribInfo.size(); ++i)
  {
    std::string typeString = "unknowType";

    switch (_interleavedAttribInfo[i]._numElements)
    {
      case 1:
        typeString = "float";
        break;
      case 2:
        typeString = "vec2";
        break;
      case 3:
        typeString = "vec3";
        break;
      case 4:
        typeString = "vec4";
        break;
      case 6:
        typeString = "mat2";
        break;
      case 12:
        typeString = "mat3";
        break;
      case 16:
        typeString = "mat4";
        break;
    }

    layoutString += "layout(location=" + gloost::toString(i) + ") in " + typeString + " " +  _interleavedAttribInfo[i]._name + ";\n";
  }

  layoutString += "\n";

  return layoutString;
}


////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


