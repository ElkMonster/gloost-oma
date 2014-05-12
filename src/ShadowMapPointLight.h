
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



#ifndef GLOOST_SHADOWMAPPOINTLIGHT_H
#define GLOOST_SHADOWMAPPOINTLIGHT_H



/// gloost includes
#include <Fbo.h>
#include <PointLight.h>
#include <Viewport.h>
#include <PerspectiveCamera.h>
#include <Texture.h>



namespace gloost
{

  /// PointLight with build in ShadowMap creation

class ShadowMapPointLight : public PointLight
{

  public:

    /// class constructor
    ShadowMapPointLight(unsigned int smap_width,
                        unsigned int smap_height);

    /* virtual */ ~ShadowMapPointLight();



    /// start shadowmap pass with this call. sceneMin and sceneMax defines the bounding box of the area with shadow
    void beginUniformShadowMapCreation(const Point3& sceneMin,
                                       const Point3& sceneMax,
                                       const Camera* cam);

    void beginUniformShadowMapCreation(const Point3& sceneMin,
                                       const Point3& sceneMax);

    /// end the shadowMap pass with this call
    void endShadowMapCreation();

    void applyShadowMapMatrix(const Camera* cam);

    /// returns the Id of the shadowmap within the texture manager
    unsigned int getShadowMapId();


    /// set value for glPolygonOffset
    void setPolygonOffsetFactor(float factor);
    void setPolygonOffsetUnits(float units);

 private:

    Viewport _viewport;
    PerspectiveCamera*   _camera;
    Fbo*     _fbo;
    Texture* _shadowMapTexture;
    unsigned int _shadowMapTexture_handle;
    unsigned int _shadowMapTexture_id;


    float _polygonOffsetFactor;
    float _polygonOffsetUnits;


};


} // namespace gloost


#endif // GLOOST_SHADOWMAPPOINTLIGHT_H
