
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



/// gloost system includes
#include <graph/Core.h>
#include <graph/Action.h>
#include <graph/PointLightCore.h>

#include <PointLight.h>
#include <gloostRenderGoodies.h>


/// cpp includes





namespace gloost
{



////////////////////////////////////////////////////////////////////////////////


 /// class constructor

PointLightCore::PointLightCore(GLenum glLightNum):
  Core(GLOOST_CORE_POINTLIGHT),
  _glLightNum(glLightNum),
  _pointLight(new gloost::PointLight()),
  _beacon(0),
  _visualSize(0.5)
{
  _pointLight->setPosition(gloost::Point3(0.0, 0.0, 0.0));
  _pointLight->setAmbient(gloost::Point3(0.01, 0.01, 0.01));
  _pointLight->setDiffuse(gloost::Point3(0.4, 0.4, 0.4));
  _pointLight->setSpecular(gloost::Point3(0.8, 0.8, 0.8));
}


////////////////////////////////////////////////////////////////////////////////


 /// class constructor

PointLightCore::PointLightCore(PointLight* pointLight, GLenum glLightNum):
  Core(GLOOST_CORE_POINTLIGHT),
  _glLightNum(glLightNum),
  _pointLight(pointLight),
  _beacon(0),
  _visualSize(0.5)
{

}


////////////////////////////////////////////////////////////////////////////////


 /// class destructor

PointLightCore::~PointLightCore()
{
//  delete _pointLight;
}


////////////////////////////////////////////////////////////////////////////////


 ///

/* virtual */
void
PointLightCore::enterCore (const Action* action)
{
  if (isEnabled())
  {
    Matrix worldToLightNode;
    worldToLightNode = action->getCurrentNode()->toWorld();
    worldToLightNode.invert();

    Matrix beaconToWorldMatrix;

    if (_beacon)
    {
      beaconToWorldMatrix = _beacon->toWorld();
      beaconToWorldMatrix.mult(worldToLightNode);
    }
    else
    {
      beaconToWorldMatrix.setIdentity();

      std::cout << std::endl;
      std::cout << std::endl << "Warning in PointLightCore::enterCore (const Action* action) on SharedResource " << getSharedResourceId() << ":";
      std::cout << std::endl << "         This gloost::PointLight has no Beacon!";
      std::cout << std::endl << "         Use void PointLightCore::setBeacon(Node* beaconNode)";
      std::cout << std::endl << "         to set one!";
      std::flush(std::cout);
      return;
    }


    glPushMatrix();
    {
//      glLoadIdentity();

      gloostMultMatrix(beaconToWorldMatrix.data());
      _pointLight->set(_glLightNum);

      /// draw yellow box on light position
      if (_visualSize)
      {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        {
          glDisable(GL_LIGHTING);

          gloost::vec4 lightColor = _pointLight->getSpecular();

          glColor4f(lightColor.r, lightColor.g, lightColor.b, 1.0);
          glScalef(_visualSize, _visualSize, _visualSize);
          glPushMatrix();
          {

            gloost::drawWireCircle12();
            glRotated(90.0, 1.0, 0.0, 0.0);
            gloost::drawWireCircle12();
            glRotated(90.0, 0.0, 1.0, 0.0);
            gloost::drawWireCircle12();
          }
          glPopMatrix();
        }
        glPopAttrib();
      }


    }
    glPopMatrix();
  }

}


////////////////////////////////////////////////////////////////////////////////


 ///

/* virtual */
void
PointLightCore::exitCore (const Action* action)
{
	_pointLight->disable();
}


////////////////////////////////////////////////////////////////////////////////


 /// get the point light

PointLight*
PointLightCore::getPointLight() const
{
	return _pointLight;
}


////////////////////////////////////////////////////////////////////////////////


  /// get the light beacon node (node that determines light position)

Node*
PointLightCore::getBeacon() const
{
	return _beacon;
}


////////////////////////////////////////////////////////////////////////////////


/// set the light beacon node (node that determines light position)
void
PointLightCore::setBeacon(Node* beaconNode)
{
	_beacon = beaconNode;
}


////////////////////////////////////////////////////////////////////////////////


  /// get glLight number for this light

GLenum
PointLightCore::getGlLightNum() const
{
	return _glLightNum;
}


////////////////////////////////////////////////////////////////////////////////


  /// set glLight number for this light

void
PointLightCore::setGlLightNum(GLenum glLightNum)
{
	_glLightNum = glLightNum;
}


////////////////////////////////////////////////////////////////////////////////


} // namespace gloost

