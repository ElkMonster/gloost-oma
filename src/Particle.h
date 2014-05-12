
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



#ifndef GLOOST_PARTICLE_H
#define GLOOST_PARTICLE_H


/// objfile system includes
#include <Vector3.h>
#include <UniformTypes.h>


/// cpp includes
#include <string>



namespace gloost
{


//////////////////////////////////////////////////////////////////////////////////////////


  ///  A Particle

class Particle
{
	public:

    /// class constructor
    Particle();

    /// class destructor
	  ~Particle();


    Point3 position;
    Point3 position2;

    Vector3 speed;
    Vector3 lastspeed;
    Vector3 acceleration;

    Vector3 rotation;
    Vector3 rotationSpeed;
    Vector3 rotationAcceleration;

    Vector3 scale;
    Vector3 scaleSpeed;
    Vector3 scaleAcceleration;

    vec4 color;

    float   lifetime;
    float   maxLifetime;
    float   weight;
    float   size;
    float   bouncynes;

    unsigned int index;

  private:


};


} // namespace gloost


#endif // GLOOST_PARTICLE_H


