
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


#ifndef H_GLOOST_MESH_GOODIES
#define H_GLOOST_MESH_GOODIES

#include <Mesh.h>
#include <Point3.h>
#include <Vector3.h>
#include <gloostMath.h>

///////////////////////////////////////////////////////////////////////////////


namespace gloost
{


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (0.0,0.0,0.0) and (1.0,1.0,1.0) build with two triangles
  \remarks ...
*/

gloost::Mesh*
createTriangleQuad(float sMin=0.0, float sMax=1.0,
                   float tMin=0.0, float tMax=1.0,
                   const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = new gloost::Mesh();

  // vertices
  mesh->getVertices().push_back(Point3(0.0, 0.0, 0.0));
  mesh->getVertices().push_back(Point3(0.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 0.0, 0.0));
  mesh->getVertices().push_back(Point3(0.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 1.0, 0.0));

  // normals
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));

  // colors
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);

  // texcoords
  mesh->getTexCoords().push_back(Point3(sMin, tMin, 0.0));
  mesh->getTexCoords().push_back(Point3(sMin, tMax, 0.0));
  mesh->getTexCoords().push_back(Point3(sMax, tMin, 0.0));
  mesh->getTexCoords().push_back(Point3(sMin, tMax, 0.0));
  mesh->getTexCoords().push_back(Point3(sMax, tMax, 0.0));

  // indices
  mesh->getTriangles().push_back(TriangleFace(0,1,2));
  mesh->getTriangles().push_back(TriangleFace(2,3,4));

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (-0.5,-0.5,-0.5) and (0.5,0.5,0.5) build with two triangles
  \remarks Can be drawn as GL_TRIANGLES and GL_TRIANGLE_STRIP
*/

gloost::Mesh*
createTriangleQuadCenter(float sMin=0.0, float sMax=1.0,
                         float tMin=0.0, float tMax=1.0,
                         const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = createTriangleQuad(sMin, sMax, tMin, tMax, color);

  // vertices
  mesh->getVertices()[0] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[1] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[2] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[3] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[4] -= gloost::Vector3(0.5, 0.5, 0.0);

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (0.0,0.0,0.0) and (1.0,1.0,1.0) build with two triangles
  \remarks ...
*/

gloost::Mesh*
createQuad(float sMin=0.0, float sMax=1.0,
           float tMin=0.0, float tMax=1.0,
           const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = new gloost::Mesh();

  // vertices
  mesh->getVertices().push_back(Point3(0.0, 0.0, 0.0));
  mesh->getVertices().push_back(Point3(0.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 0.0, 0.0));

  // normals
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));

  // colors
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);

  // texcoords
  mesh->getTexCoords().push_back(Point3(sMin, tMin, 0.0));
  mesh->getTexCoords().push_back(Point3(sMin, tMax, 0.0));
  mesh->getTexCoords().push_back(Point3(sMax, tMax, 0.0));
  mesh->getTexCoords().push_back(Point3(sMax, tMin, 0.0));

  // indices
  mesh->getQuads().push_back(QuadFace(0,1,2,3));

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (-0.5,-0.5,-0.5) and (0.5,0.5,0.5) build with two triangles
  \remarks ...
*/

gloost::Mesh*
createQuadCenter(float sMin=0.0, float sMax=1.0,
                 float tMin=0.0, float tMax=1.0,
                 const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = createQuad(sMin, sMax, tMin, tMax, color);

  // vertices
  mesh->getVertices()[0] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[1] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[2] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[3] -= gloost::Vector3(0.5, 0.5, 0.0);

  return mesh;

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (0.0,0.0,0.0) and (1.0,1.0,1.0) build with four lines
  \remarks ...
*/

gloost::Mesh*
createLineQuad(float sMin=0.0, float sMax=1.0,
               float tMin=0.0, float tMax=1.0,
               const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = new gloost::Mesh();

  // vertices
  mesh->getVertices().push_back(Point3(0.0, 0.0, 0.0));
  mesh->getVertices().push_back(Point3(0.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 1.0, 0.0));
  mesh->getVertices().push_back(Point3(1.0, 0.0, 0.0));

  // normals
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));
  mesh->getNormals().push_back(Vector3(0.0, 0.0, 1.0));

  // colors
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);
  mesh->getColors().push_back(color);

  // indices
  mesh->getLines().push_back(Line(0,1));
  mesh->getLines().push_back(Line(1,2));
  mesh->getLines().push_back(Line(2,3));
  mesh->getLines().push_back(Line(3,0));

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a Quad located between (-0.5,-0.5,-0.5) and (0.5,0.5,0.5) build with four lines
  \remarks ...
*/

gloost::Mesh*
createLineQuadCenter(float sMin=0.0, float sMax=1.0,
                     float tMin=0.0, float tMax=1.0,
                     const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = createLineQuad(sMin, sMax, tMin, tMax, color);

  // vertices
  mesh->getVertices()[0] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[1] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[2] -= gloost::Vector3(0.5, 0.5, 0.0);
  mesh->getVertices()[3] -= gloost::Vector3(0.5, 0.5, 0.0);

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a circle with numSegments segments build with triangles
  \remarks Can be drawn as GL_TRIANGLES, GL_TRIANGLE_STRIP and GL_LINE_STRIP
*/

gloost::Mesh*
createTriangleCircle(unsigned numSegments = 18,
                     float    radius = 0.5,
                     const    vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = new gloost::Mesh();

  float stepWidth = (2*PI)/(float)numSegments;

  mesh->getVertices().push_back(gloost::Point3(0.0, 0.0, 0.0));
  mesh->getNormals().push_back(gloost::Point3(0.0, 0.0, 1.0));
  mesh->getColors().push_back(color);
  mesh->getTexCoords().push_back(Point3(0.5, 0.5, 0.0));


  // vertices, normals and texcoords
  for (unsigned i=0; i!=numSegments+1; ++i)
  {
    mesh->getVertices().push_back(gloost::Point3(sin(i*stepWidth)*radius, cos(i*stepWidth)*radius, 0.0));
    mesh->getNormals().push_back(gloost::Point3(0.0, 0.0, 1.0));
    mesh->getColors().push_back(color);
    mesh->getTexCoords().push_back(gloost::Point3(sin(i*stepWidth)*0.5+1.0, cos(i*stepWidth)*0.5+1.0, 0.0));
  }

  // indices
  for (int i=1; i!=(int)numSegments+2; ++i)
  {
    mesh->getTriangles().push_back(TriangleFace(0, i-1, i));
  }

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a circle with numSegments segments build with triangles
  \remarks Can be drawn as GL_TRIANGLES, GL_TRIANGLE_STRIP and GL_LINE_STRIP
*/

gloost::Mesh*
createLineCircle(unsigned numSegments = 18,
                 float radius = 0.5,
                 const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  Mesh* mesh = new gloost::Mesh();

  float stepWidth = (2*PI)/(float)numSegments;

  // vertices and colors
  for (unsigned i=0; i!=numSegments+1; ++i)
  {
    mesh->getVertices().push_back(gloost::Point3(sin(i*stepWidth)*radius, cos(i*stepWidth)*radius, 0.0));
    mesh->getColors().push_back(color);
  }

  // indices
  for (int i=1; i!=(int)numSegments+1; ++i)
  {
    mesh->getLines().push_back(Line(i-1, i));
  }


  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a line grid between (0.0,0.0,0.0) and (1.0,1.0,1.0)
  \remarks ...
*/

gloost::Mesh*
createLineGrid(unsigned numColums,
               unsigned numRows,
               const vec4& color = vec4(1.0,1.0,1.0,1.0))
{

  gloost::Mesh* mesh = new gloost::Mesh();

  unsigned vertexindex = 0;

  float step = 1.0f/numColums;
  for(unsigned int i=0; i != numColums+1; ++i)
  {
    mesh->getVertices().push_back( Point3(step*i,  1.0, 0.0));
    mesh->getVertices().push_back( Point3(step*i,  0.0, 0.0));

    mesh->getColors().push_back(color);
    mesh->getColors().push_back(color);

    mesh->getLines().push_back(Line(vertexindex, vertexindex+1));
    vertexindex += 2;
  }

  step = 1.0f/numRows;
  for(unsigned int i=0; i != numRows+1; ++i)
  {
    mesh->getVertices().push_back( Point3(1.0, step*i, 0.0));
    mesh->getVertices().push_back( Point3(0.0, step*i, 0.0));

    mesh->getColors().push_back(color);
    mesh->getColors().push_back(color);

    mesh->getLines().push_back(Line(vertexindex, vertexindex+1));
    vertexindex += 2;
  }

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a line grid between (0.0,0.0,0.0) and (1.0,1.0,1.0)
  \remarks ...
*/

gloost::Mesh*
createLineGridCenter(unsigned int numColums,
                     unsigned numRows,
                     const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  gloost::Mesh* mesh = createLineGrid(numColums, numRows, color);

  for (unsigned i=0; i!=mesh->getVertices().size(); ++i)
  {
    mesh->getVertices()[i] -= gloost::Vector3(0.5, 0.5, 0.0);
  }

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates an arrow, pointing up, build with lines
  \remarks ...
*/

gloost::Mesh*
createTriangleArrow(const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  gloost::Mesh* mesh = new gloost::Mesh();

  mesh->getVertices().push_back(gloost::Point3( 0.0,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.5, -0.2,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.5,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.0,  0.2,  0.0f));
  mesh->getVertices().push_back(gloost::Point3(-0.5,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3(-0.5, -0.2,  0.0f));

  // normals and colors and texcoords
  for (unsigned i=0; i!=6; ++i)
  {
    mesh->getNormals().push_back(gloost::Vector3(0.0,0.0,1.0));
    mesh->getColors().push_back(color);
    mesh->getTexCoords().push_back(mesh->getVertices()[i] + gloost::Vector3(0.5, 0.5, 0.0));
  }

  for (unsigned i=0; i!=mesh->getVertices().size()-1; ++i)
  {
    mesh->getTriangles().push_back(TriangleFace(0, i, i+1));
  }

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates an arrow, pointing up, build with lines
  \remarks ...
*/

gloost::Mesh*
createLineArrow(const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  gloost::Mesh* mesh = new gloost::Mesh();

  mesh->getVertices().push_back(gloost::Point3( 0.0,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.5, -0.2,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.5,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3( 0.0,  0.2,  0.0f));
  mesh->getVertices().push_back(gloost::Point3(-0.5,  0.0,  0.0f));
  mesh->getVertices().push_back(gloost::Point3(-0.5, -0.2,  0.0f));

  // normals and colors
  for (unsigned i=0; i!=6; ++i)
  {
    mesh->getColors().push_back(color);
  }

  for (unsigned i=0; i!=mesh->getVertices().size()-1; ++i)
  {
    mesh->getLines().push_back(Line(i, i+1));
  }
  mesh->getLines().push_back(Line(5, 0));

  return mesh;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a box from (0.0,0.0,0.0) to (sideLength,sideLength,sideLength)
  \remarks ...
*/

gloost::Mesh*
createQuadBox(float sideLength = 1.0, const vec4& color = vec4(1.0,1.0,1.0,1.0))
{
  gloost::Mesh* mesh = new gloost::Mesh();

  gloost::Point3 A = gloost::Point3(-0.5, -0.5, 0.5)*sideLength;
  gloost::Point3 B = gloost::Point3(0.5, -0.5, 0.5)*sideLength;
  gloost::Point3 C = gloost::Point3(-0.5, -0.5, -0.5)*sideLength;
  gloost::Point3 D = gloost::Point3(0.5, -0.5, -0.5)*sideLength;
  gloost::Point3 E = gloost::Point3(-0.5, 0.5, 0.5)*sideLength;
  gloost::Point3 F = gloost::Point3(0.5, 0.5, 0.5)*sideLength;
  gloost::Point3 G = gloost::Point3(-0.5, 0.5, -0.5)*sideLength;
  gloost::Point3 H = gloost::Point3(0.5, 0.5, -0.5)*sideLength;

  mesh->getVertices() = std::vector<Point3>(24);
  mesh->getNormals()  = std::vector<Vector3>(24);
  mesh->getColors()   = std::vector<vec4>(24);


  gloost::Vector3 normal;

//  int index = 0;

// top: EGF + GHF
  normal = gloost::Vector3(0.0, 1.0, 0.0);

  mesh->getVertices()[0] = (E);
  mesh->getNormals()[0] = (normal);
  mesh->getColors()[0] = (color);

  mesh->getVertices()[1] = (G);
  mesh->getNormals()[1] = (normal);
  mesh->getColors()[1] = (color);

  mesh->getVertices()[2] = (F);
  mesh->getNormals()[2] = (normal);
  mesh->getColors()[2] = (color);

  mesh->getVertices()[3] = (H);
  mesh->getNormals()[3] = (normal);
  mesh->getColors()[3] = (color);

//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(3, 2, 0, 1));




// left: CGA + GEA
  normal = gloost::Vector3(-1.0, 0.0, 0.0);

  mesh->getVertices()[4] = (C);
  mesh->getNormals()[4] = (normal);
  mesh->getColors()[4] = (color);

  mesh->getVertices()[5] = (G);
  mesh->getNormals()[5] = (normal);
  mesh->getColors()[5] = (color);

  mesh->getVertices()[6] = (A);
  mesh->getNormals()[6] = (normal);
  mesh->getColors()[6] = (color);

  mesh->getVertices()[7] = (E);
  mesh->getNormals()[7] = (normal);
  mesh->getColors()[7] = (color);


//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(7, 6, 4, 5));


// front: AEB + EFB
  normal = gloost::Vector3(0.0, 0.0, 1.0);

  mesh->getVertices()[8] = (A);
  mesh->getNormals()[8] = (normal);
  mesh->getColors()[8] = (color);

  mesh->getVertices()[9] = (E);
  mesh->getNormals()[9] = (normal);
  mesh->getColors()[9] = (color);

  mesh->getVertices()[10] = (B);
  mesh->getNormals()[10] = (normal);
  mesh->getColors()[10] = (color);

  mesh->getVertices()[11] = (F);
  mesh->getNormals()[11] = (normal);
  mesh->getColors()[11] = (color);


//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(11, 10, 8, 9));


// right: BFD + FHD
  normal = gloost::Vector3(1.0, 0.0, 0.0);

  mesh->getVertices()[12] = (B);
  mesh->getNormals()[12] = (normal);
  mesh->getColors()[12] = (color);

  mesh->getVertices()[13] = (F);
  mesh->getNormals()[13] = (normal);
  mesh->getColors()[13] = (color);

  mesh->getVertices()[14] = (D);
  mesh->getNormals()[14] = (normal);
  mesh->getColors()[14] = (color);

  mesh->getVertices()[15] = (H);
  mesh->getNormals()[15] = (normal);
  mesh->getColors()[15] = (color);


//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(15, 14, 12, 13));

// bottom: CAD + ABD
  normal = gloost::Vector3(0.0, -1.0, 0.0);

  mesh->getVertices()[16] = (C);
  mesh->getNormals()[16] = (normal);
  mesh->getColors()[16] = (color);


  mesh->getVertices()[17] = (A);
  mesh->getNormals()[17] = (normal);
  mesh->getColors()[17] = (color);

  mesh->getVertices()[18] = (D);
  mesh->getNormals()[18] = (normal);
  mesh->getColors()[18] = (color);

  mesh->getVertices()[19] = (B);
  mesh->getNormals()[19] = (normal);
  mesh->getColors()[19] = (color);


//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(19, 18, 16, 17));

// back: GCH + CDH
  normal = gloost::Vector3(0.0, 0.0, -1.0);

  mesh->getVertices()[20] = (G);
  mesh->getNormals()[20] = (normal);
  mesh->getColors()[20] = (color);

  mesh->getVertices()[21] = (C);
  mesh->getNormals()[21] = (normal);
  mesh->getColors()[21] = (color);

  mesh->getVertices()[22] = (H);
  mesh->getNormals()[22] = (normal);
  mesh->getColors()[22] = (color);

  mesh->getVertices()[23] = (D);
  mesh->getNormals()[23] = (normal);
  mesh->getColors()[23] = (color);

//    triangles.push_back(gloost::TriangleFace(index, index+1, index+2));
//    triangles.push_back(gloost::TriangleFace(index+1, index+3, index+2));

  mesh->getQuads().push_back(gloost::QuadFace(23, 22, 20, 21));


  return mesh;
}


///////////////////////////////////////////////////////////////////////////////




}  // namespace gloost


#endif // #ifndef H_GLOOST_MESH_GOODIES



