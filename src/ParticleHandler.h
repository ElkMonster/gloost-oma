
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



#ifndef GLOOST_PARTICLEHANDLER_H
#define GLOOST_PARTICLEHANDLER_H



/// gloost system includes
#include <Point3.h>
#include <Particle.h>



/// cpp includes

#include <list>
#include <vector>



namespace gloost
{


  ///  Container to handle ParticleSprites

class ParticleHandler
{
	public:
    /// class constructor
    ParticleHandler();

    /// class destructor
    virtual ~ParticleHandler();


    typedef std::list<Particle*>::iterator       particleIterator;
    typedef std::list<Particle*>::const_iterator particleConstIterator;


    /// Add a sprite
    void addParticle(Particle* particle);
    void addParticleOnFront(Particle* particle);


    /// (I.)   lifetime -= 1  and deletes all particles with lifetime < 0;
    virtual void handleLifeTimes(float steps = 1.0);


    /// (II.)  move your particles
    virtual void frameStep(float steps = 1.0);


    /// (III.)  draw the particles
    virtual void draw();




    /// Delete all particles
    virtual void clear();


    /// sort the particles by distance to a point
//    virtual bool sortByDistance(const gloost::Point3& cameraPoint);
//
//    virtual bool distCompareFunk(Particle* left, Particle* right);


    /// return number of particles
    int size() const;

    /// get List Iterators
    particleIterator getParticlesBegin();
    particleIterator getParticlesEnd();

    /// remove one entry
    void remove(ParticleHandler::particleIterator it);

	protected:


    /// Particles
    std::list<Particle*> _particleList;

    /// offset to the location off all particles
    Point3 _locOffset;

    Point3 _cameraPosition;


};


} // gloost


#endif // GLOOST_PARTICLEHANDLER_H



