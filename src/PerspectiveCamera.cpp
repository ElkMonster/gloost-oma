
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
#include <PerspectiveCamera.h>
#include <gloostConfig.h>
#include <gloostGlUtil.h>
#include <gloostMath.h>



/// cpp includes



namespace gloost
{


///////////////////////////////////////////////////////////////////////////////


/// class constructor
PerspectiveCamera::PerspectiveCamera():
    Camera()
{

}


///////////////////////////////////////////////////////////////////////////////


/// class constructor
PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& perpCamera):
    Camera(perpCamera._fov, perpCamera._aspect, perpCamera._nearPlaneZ, perpCamera._farPlaneZ )
{
  this->_projection_dirty = perpCamera._projection_dirty;

//  this->_projection = perpCamera._projection;
//  this->_modelview  = perpCamera._modelview;
//  this->_frustum    = perpCamera._frustum;
}


///////////////////////////////////////////////////////////////////////////////


  ///

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
  : Camera(fov, aspect, near, far)
{

}


///////////////////////////////////////////////////////////////////////////////


  ///

/*virtual*/
PerspectiveCamera::~PerspectiveCamera()
{

}


///////////////////////////////////////////////////////////////////////////////


  ///

void
PerspectiveCamera::setFov(float fov)
{
  _fov = fov;
  _projection_dirty = true;
}


///////////////////////////////////////////////////////////////////////////////


  ///

float
PerspectiveCamera::getFov() const
{
  return _fov;
}


///////////////////////////////////////////////////////////////////////////////


  ///

void
PerspectiveCamera::setAspect(float aspect)
{
  _aspect = aspect;
  _projection_dirty = true;
}


///////////////////////////////////////////////////////////////////////////////


  ///
float
PerspectiveCamera::getAspect() const
{
  return _aspect;
}


///////////////////////////////////////////////////////////////////////////////


  ///

void PerspectiveCamera::setNear(float nearPlaneZ)
{
  _nearPlaneZ = nearPlaneZ;
  _projection_dirty = true;
}


///////////////////////////////////////////////////////////////////////////////


  ///

float
PerspectiveCamera::getNear() const
{
  return _nearPlaneZ;
}


///////////////////////////////////////////////////////////////////////////////


  ///

void PerspectiveCamera::setFar(float farPlaneZ)
{
  _farPlaneZ = farPlaneZ;
  _projection_dirty = true;
}


///////////////////////////////////////////////////////////////////////////////


  ///

float
PerspectiveCamera::getFar() const
{
  return _farPlaneZ;
}


///////////////////////////////////////////////////////////////////////////////


  ///

/* virtual */
void PerspectiveCamera::set()
{

  if(_projection_dirty)
  {
    updateProjection();
    updateFrustum();
  }

  Camera::set();
}


///////////////////////////////////////////////////////////////////////////////


  /// calculates a modelview matrix from given position, point to look at and down vector of the camera

void
PerspectiveCamera::lookAt(const Point3&  cameraPosition,
                          const Point3&  pointToLookAt,
                          const Vector3& upVector)
{

  _cameraPosition = cameraPosition;

#if 0

//  glMatrixMode(GL_MODELVIEW);
//
//  glLoadIdentity();
//
//  glPushMatrix();
//  {
//    glLoadIdentity();
//    gluLookAt((GLfloat) cameraPosition[0],(GLfloat) cameraPosition[1],(GLfloat) cameraPosition[2],
//              (GLfloat) pointToLookAt[0],(GLfloat) pointToLookAt[1],(GLfloat) pointToLookAt[2],
//              (GLfloat) upVector[0], (GLfloat) upVector[1], (GLfloat) upVector[2]);
//    gloostGetv (GL_MODELVIEW_MATRIX, _modelview.data());
//
//
//  }
//  glPopMatrix();

#else

    _modelview.setIdentity();
    gloost::gloostLookAt(_modelview, cameraPosition, pointToLookAt, upVector);

#endif

  updateProjection();
  updateFrustum();

}


///////////////////////////////////////////////////////////////////////////////


  /// returns position of the camera !!! Works only if position was set via lookAt(Point3 ...)

/* virtual */
const Point3&
PerspectiveCamera::getPosition()
{
  return _cameraPosition;
}


///////////////////////////////////////////////////////////////////////////////


  ///

/*virtual*/
Ray
PerspectiveCamera::getPickRay(unsigned int screenWidth,
                              unsigned int screenHeight,
                              unsigned int mouseH,
                              unsigned int mouseV)
{

  if(_projection_dirty)
  {
    updateProjection();
    updateFrustum();
  }


  Vector3 frustumH_vec         = _frustum.far_lower_right - _frustum.far_lower_left;
  Vector3 FrustumOnePixelWidth = frustumH_vec/screenWidth;

  Vector3 frustumV_vec          = _frustum.far_upper_left - _frustum.far_lower_left;
  Vector3 FrustumOnePixelHeight = frustumV_vec/screenHeight;


  Point3 pickPointOnFarPlane = _frustum.far_lower_left
                                + (FrustumOnePixelWidth * mouseH)
                                + (FrustumOnePixelHeight * mouseV);


  Matrix modelviewInv = _modelview;
  modelviewInv.invert();

  Point3 camPos = modelviewInv * Point3(0.0, 0.0, 0.0);
  Vector3 pickDir = (pickPointOnFarPlane - camPos).normalized();

  return Ray(camPos, pickDir);
}


///////////////////////////////////////////////////////////////////////////////


  /// recalc the projection matrix

/*virtual*/
void
PerspectiveCamera::updateProjection()
{
// old and deprecated ....
//  glMatrixMode(GL_PROJECTION);
//
//  glPushMatrix();
//  {
//    glLoadIdentity();
//    gluPerspective (_fov, _aspect, _nearPlaneZ, _farPlaneZ);
//    gloostGetv (GL_PROJECTION_MATRIX, _projection.data());
//  }
//  glPopMatrix();
//
//  glMatrixMode(GL_MODELVIEW);

  gloostPerspective(_projection, _fov, _aspect, _nearPlaneZ, _farPlaneZ);

  _projection_dirty = false;
}


///////////////////////////////////////////////////////////////////////////////


  ///

/*virtual*/
void
PerspectiveCamera::updateFrustum()
{
  const float scale = tan(gloost::PI * _fov/360.0f);
  const float near_top = _nearPlaneZ * scale;
  const float near_left  = near_top * _aspect;
  const float far_top = _farPlaneZ * scale;
  const float far_left  = far_top * _aspect;
  Matrix _modelview_inv(_modelview);
  _modelview_inv.invert();
  _frustum.near_lower_left  = _modelview_inv * Point3(-near_left,-near_top,-_nearPlaneZ);
  _frustum.near_lower_right = _modelview_inv * Point3(near_left,-near_top,-_nearPlaneZ);
  _frustum.near_upper_right = _modelview_inv * Point3(near_left,near_top,-_nearPlaneZ);
  _frustum.near_upper_left  = _modelview_inv * Point3(-near_left,near_top,-_nearPlaneZ);

  _frustum.far_lower_left  = _modelview_inv * Point3(-far_left,-far_top,-_farPlaneZ);
  _frustum.far_lower_right = _modelview_inv * Point3(far_left,-far_top,-_farPlaneZ);
  _frustum.far_upper_right = _modelview_inv * Point3(far_left,far_top,-_farPlaneZ);
  _frustum.far_upper_left  = _modelview_inv * Point3(-far_left,far_top,-_farPlaneZ);

  _frustum.recalcPlanes();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace gloost
