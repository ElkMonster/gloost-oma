
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

            gloost is being created by Felix Weiﬂig and Stephan Beck

     Felix Weiﬂig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



/// gloost includes
#include <gloostConfig.h>
#include <Camera.h>



/// cpp includes
#include <GL/glew.h>



namespace gloost
{


///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Camera::Camera():
    _cameraPosition(Point3(0.0,0.0,0.0)),
    _fov(45),
    _aspect(1.6),
    _nearPlaneZ(0.1),
    _farPlaneZ(100.0),
    _projection_dirty(true),
    _projection(),
    _modelview(),
    _frustum()
{

}


///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Camera::Camera(const Matrix& projectionMatrix, const Matrix& modelViewMatrix):
    _cameraPosition(Point3(0.0,0.0,0.0)),
    _fov(45.0),
    _aspect(0.0),
    _nearPlaneZ(0.0),
    _farPlaneZ(0.0),
    _projection_dirty(true),
    _projection(projectionMatrix),
    _modelview(modelViewMatrix),
    _frustum()
{

}


///////////////////////////////////////////////////////////////////////////////


  ///

Camera::Camera(float fov, float aspect, float nearPlaneZ, float farPlaneZ):
    _cameraPosition(Point3(0.0,0.0,0.0)),
    _fov(fov),
    _aspect(aspect),
    _nearPlaneZ(nearPlaneZ),
    _farPlaneZ(farPlaneZ),
    _projection_dirty(true),
    _projection(),
    _modelview(),
    _frustum()
{

}


///////////////////////////////////////////////////////////////////////////////


  ///

/* virtual */
Camera::~Camera()
{

}


///////////////////////////////////////////////////////////////////////////////


  ///

void Camera::setProjectionMatrix(const Matrix& projectionMatrix)
{
  _projection = projectionMatrix;
}


///////////////////////////////////////////////////////////////////////////////


  ///

void Camera::setModelViewMatrix(const Matrix& modelViewMatrix)
{
  _modelview = modelViewMatrix;
}


///////////////////////////////////////////////////////////////////////////////


  ///

/* virtual */
void Camera::set()
{
  glMatrixMode(GL_PROJECTION);
  gloostLoadMatrix(_projection.data());

  glMatrixMode(GL_MODELVIEW);
  gloostLoadMatrix(_modelview.data());
}

///////////////////////////////////////////////////////////////////////////////


  ///

const Frustum&
Camera::getFrustum() const{
  return _frustum;
}


///////////////////////////////////////////////////////////////////////////////


  ///

const Matrix&
Camera::getProjectionMatrix() const
{
  return _projection;
}


///////////////////////////////////////////////////////////////////////////////


  ///

const Matrix&
Camera::getModelViewMatrix() const
{
  return _modelview;
}


///////////////////////////////////////////////////////////////////////////////


/// returns position of the camera !!! Works only if position was set via lookAt(Point3 ...)

/*virtual*/
const Point3&
Camera::getPosition()
{
  return _cameraPosition;
}


///////////////////////////////////////////////////////////////////////////////






} // namespace gloost
