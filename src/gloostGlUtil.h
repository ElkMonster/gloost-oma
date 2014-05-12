
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



#ifndef H_GLOOST_GLOOST_GL_UTIL
#define H_GLOOST_GLOOST_GL_UTIL


#include <gloostConfig.h>
#include <gloostMath.h>
#include <Matrix.h>
#include <Vector3.h>



namespace gloost
{


void   gloostPerspective(Matrix& matrix, float fieldOfView, float aspectRatio, float nearPlaneZ, float farPlaneZ);
void   gloostFrustum(Matrix& matrix,float left,float right,float bottom,float top,float nearPlaneZ,float farPlaneZ);
void   gloostLookAt(Matrix& matrix, const Vector3& eyePosition3D, const Vector3& center3D, const Vector3& upVector3D);
Matrix modelViewMatrixToNormalMatrix(const Matrix& modelViewMatrix);




///////////////////////////////////////////////////////////////////////////////


/**
  \brief   Creates a Matrix for a perspective projection
  \remarks Code was taken from http://www.opengl.org/wiki/GluPerspective_code and
           is licensed by terms of the LGPL
*/

inline
void
gloostPerspective(Matrix& matrix,
                  float fieldOfView,
                  float aspectRatio,
                  float nearPlaneZ,
                  float farPlaneZ)
{
  float ymax, xmax;
  ymax = nearPlaneZ * tan(fieldOfView * PI / 360.0);
  //ymin = -ymax;
  //xmin = -ymax * aspectRatio;
  xmax = ymax * aspectRatio;
  gloostFrustum(matrix, -xmax, xmax, -ymax, ymax, nearPlaneZ, farPlaneZ);
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   ...
  \remarks Code was taken from http://www.opengl.org/wiki/GluPerspective_code and
           is licensed by terms of the LGPL

           From: http://www.khronos.org/message_boards/viewtopic.php?t=1014
            glFrustum multiplies the current matrix with the following matrix:
            ( 2n/(r-l)    0       (r+l)/(r-l)     0      )
            (   0       2n/(t-b)  (t+b)/(t-b)     0      )
            (   0         0       (f+n)/(n-f)  2fn/(n-f) )
            (   0         0           -1          0      )


*/

inline
void
gloostFrustum(Matrix& matrix,
              float left,
              float right,
              float bottom,
              float top,
              float nearPlaneZ,
              float farPlaneZ)
{
  float temp, temp2, temp3, temp4;
  temp = 2.0 * nearPlaneZ;
  temp2 = right - left;
  temp3 = top - bottom;
  temp4 = farPlaneZ - nearPlaneZ;
  matrix[0] = temp / temp2;
  matrix[1] = 0.0;
  matrix[2] = 0.0;
  matrix[3] = 0.0;
  matrix[4] = 0.0;
  matrix[5] = temp / temp3;
  matrix[6] = 0.0;
  matrix[7] = 0.0;
  matrix[8] = (right + left) / temp2;
  matrix[9] = (top + bottom) / temp3;
  matrix[10] = (-farPlaneZ - nearPlaneZ) / temp4;
  matrix[11] = -1.0;
  matrix[12] = 0.0;
  matrix[13] = 0.0;
  matrix[14] = (-temp * farPlaneZ) / temp4;
  matrix[15] = 0.0;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   Computes a modelview matrix for a viewer, looking to a point of interest
  \remarks Code was taken from http://www.opengl.org/wiki/GluPerspective_code and
           is licensed by terms of the LGPL
*/

inline
void
gloostLookAt(Matrix& matrix, const Vector3& eyePosition3D,
             const Vector3& center3D, const Vector3& upVector3D )
{
  Vector3 forward, side, up;
  //------------------
  forward = center3D - eyePosition3D;
  forward.normalize();
  //------------------
  //Side = forward x up
  side = cross(forward, upVector3D);
  side.normalize();
  //------------------
  //Recompute up as: up = side x forward
  up = cross(side, forward);
  up.normalize();
  //------------------
  matrix[0]  = side[0];
  matrix[4]  = side[1];
  matrix[8]  = side[2];
//  matrix[12] = 0.0;
  //------------------
  matrix[1]  = up[0];
  matrix[5]  = up[1];
  matrix[9]  = up[2];
//  matrix[13] = 0.0;
  //------------------
  matrix[2]  = -forward[0];
  matrix[6]  = -forward[1];
  matrix[10] = -forward[2];
//  matrix[14] = 0.0;
  //------------------
  matrix[3]  = matrix[7] = matrix[11] = 0.0;
  matrix[15] = 1.0;
  //------------------
//  resultMatrix = matrix * matrix2;

  Matrix trans;
  trans.setIdentity();
  trans.setTranslate(eyePosition3D*-1);


  matrix = matrix*trans;

//  matrix[12] -= eyePosition3D[0];
//  matrix[13] -= eyePosition3D[1];
//  matrix[14] -= eyePosition3D[2];
}



///////////////////////////////////////////////////////////////////////////////


/**
  \brief   Converts a ModelViewMatrix into a NormalMatrix
  \remarks
*/

inline
Matrix
modelViewMatrixToNormalMatrix(const Matrix& modelViewMatrix)
{
  return modelViewMatrix.inverted().transposed();
}


///////////////////////////////////////////////////////////////////////////////


}  // namespace gloost


#endif // #ifndef H_GLOOST_GLOOST_GL_UTIL
