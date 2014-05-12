
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
#include <GbmWriter.h>
#include <Mesh.h>
#include <BinaryFile.h>



/// cpp includes
#include <vector>


namespace gloost
{

/**
  \class GbmWriter

  \brief Writer for Gloost Binary Mesh format v1.0

  \author  Felix Weiszig
  \date    March 2011
  \remarks ...
*/


///////////////////////////////////////////////////////////////////////////////


/**
  \brief class constructor
  \param ...
  \remarks ...
*/

GbmWriter::GbmWriter():
    MeshWriter()
{

}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief class constructor
  \param ...
  \remarks ...
*/

/*virtual*/
GbmWriter::~GbmWriter()
{

}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief writes a mesh to a file
  \param ...
  \remarks ...
*/

/*virtual*/
bool
GbmWriter::write(const std::string& filePath, Mesh* mesh)
{
  return writeFile(filePath,mesh);
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief writes a mesh to a file
  \param ...
  \remarks ...
*/

/*virtual*/
bool
GbmWriter::writeFile(const std::string& filePath, Mesh* mesh)
{
  std::vector<Point3>&       srcPositions = mesh->getVertices();
  std::vector<Vector3>&      srcNormals   = mesh->getNormals();
  std::vector<vec4>&         srcColors    = mesh->getColors();
  std::vector<Point3>&       srcTexCoords = mesh->getTexCoords();
  std::vector<float>&        scrInterleavedAttributes = mesh->getInterleavedAttributes();
  std::vector<Line>&         srcLines       = mesh->getLines();
  std::vector<TriangleFace>& srcTriangles = mesh->getTriangles();
  std::vector<QuadFace>&     srcQuads     = mesh->getQuads();


  // number of different things to store in the file
  unsigned int featureCount = 0;
  std::string identityString  = "GBM 1.0 ";
  std::string featureString;

  if (srcPositions.size())
  {
    ++featureCount;
    featureString += "positions: " + gloost::toString(srcPositions.size()) + " ";
  }
  if (srcNormals.size())
  {
    ++featureCount;
    featureString += "normals: " + gloost::toString(srcNormals.size()) + " ";
  }
  if (srcColors.size())
  {
    ++featureCount;
    featureString += "colors: " + gloost::toString(srcColors.size()) + " ";
  }
  if (srcTexCoords.size())
  {
    ++featureCount;
    featureString += "texcoords: " + gloost::toString(srcTexCoords.size()) + " ";
  }


  if (scrInterleavedAttributes.size())
  {
    ++featureCount;

    std::string  interleavedFeatureString = "";
    unsigned int interleavedFeatureCount  = 0;

    if (mesh->isInterleavedAttributeSupported(GLOOST_MESH_POSITIONS))
    {
      ++interleavedFeatureCount;
      interleavedFeatureString += "ipositions ";
    }
    if (mesh->isInterleavedAttributeSupported(GLOOST_MESH_NORMALS))
    {
      ++interleavedFeatureCount;
      interleavedFeatureString += "inormals ";
    }
    if (mesh->isInterleavedAttributeSupported(GLOOST_MESH_COLORS))
    {
      ++interleavedFeatureCount;
      interleavedFeatureString += "icolors ";
    }
    if (mesh->isInterleavedAttributeSupported(GLOOST_MESH_TEXCOORDS))
    {
      ++interleavedFeatureCount;
      interleavedFeatureString += "itexcoords ";
    }

    interleavedFeatureString = "interleaved: "
                               + gloost::toString(interleavedFeatureCount) + " "
                               + gloost::toString(mesh->getInterleavedAttributes().size())
                               + std::string(" ")
                               + interleavedFeatureString;


    featureString += interleavedFeatureString;
  }









  if (srcLines.size())
  {
    ++featureCount;
    featureString += "lines: " + gloost::toString(srcLines.size()) + " ";
  }
  if (srcTriangles.size())
  {
    ++featureCount;
    featureString += "triangles: " + gloost::toString(srcTriangles.size()) + " ";
  }
  if (srcQuads.size())
  {
    ++featureCount;
    featureString += "quads: " + gloost::toString(srcQuads.size()) + " ";
  }


  // set the number of features before the features itself
  featureString = "features: " + gloost::toString(featureCount) + " " + featureString;
  std::string headerString = identityString + featureString;


  BinaryFile file;

  if (!file.openToWrite(filePath))
  {
    return false;
  }


  file.writeString(headerString);


  for (unsigned int i=0; i!=srcPositions.size(); ++i)
  {
    file.writeFloat32(srcPositions[i][0]);
    file.writeFloat32(srcPositions[i][1]);
    file.writeFloat32(srcPositions[i][2]);
  }
  for (unsigned int i=0; i!=srcNormals.size(); ++i)
  {
    file.writeFloat32(srcNormals[i][0]);
    file.writeFloat32(srcNormals[i][1]);
    file.writeFloat32(srcNormals[i][2]);
  }
  for (unsigned int i=0; i!=srcColors.size(); ++i)
  {
    file.writeFloat32(srcColors[i].r);
    file.writeFloat32(srcColors[i].g);
    file.writeFloat32(srcColors[i].b);
    file.writeFloat32(srcColors[i].a);
  }
  for (unsigned int i=0; i!=srcTexCoords.size(); ++i)
  {
    file.writeFloat32(srcTexCoords[i][0]);
    file.writeFloat32(srcTexCoords[i][1]);
    file.writeFloat32(srcTexCoords[i][2]);
  }
  for (unsigned int i=0; i!=scrInterleavedAttributes.size(); ++i)
  {
    file.writeFloat32(scrInterleavedAttributes[i]);
  }
  for (unsigned int i=0; i!=srcLines.size(); ++i)
  {
    file.writeFloat32(srcLines[i].vertexIndices[0]);
    file.writeFloat32(srcLines[i].vertexIndices[1]);
  }
  for (unsigned int i=0; i!=srcTriangles.size(); ++i)
  {
    file.writeFloat32(srcTriangles[i].vertexIndices[0]);
    file.writeFloat32(srcTriangles[i].vertexIndices[1]);
    file.writeFloat32(srcTriangles[i].vertexIndices[2]);
  }
  for (unsigned int i=0; i!=srcQuads.size(); ++i)
  {
    file.writeFloat32(srcQuads[i].vertexIndices[0]);
    file.writeFloat32(srcQuads[i].vertexIndices[1]);
    file.writeFloat32(srcQuads[i].vertexIndices[2]);
    file.writeFloat32(srcQuads[i].vertexIndices[3]);
  }



  file.close();

  return true;
}


///////////////////////////////////////////////////////////////////////////////





} // namespace gloost

