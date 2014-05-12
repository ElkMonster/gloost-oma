
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
#include <ParticleHandler.h>




namespace gloost
{


///////////////////////////////////////////////////////////////////////////////


 /// class constructor

ParticleHandler::ParticleHandler():
  _particleList(),
  _locOffset(),
  _cameraPosition()
{


}


///////////////////////////////////////////////////////////////////////////////


 /// class destructor

/*virtual*/
ParticleHandler::~ParticleHandler()
{

}


///////////////////////////////////////////////////////////////////////////////


  /// add a particle

void
ParticleHandler::addParticle(Particle* particle)
{
  _particleList.push_back(particle);
}


///////////////////////////////////////////////////////////////////////////////


  /// add a particle

void
ParticleHandler::addParticleOnFront(Particle* particle)
{
  _particleList.push_front(particle);
}


///////////////////////////////////////////////////////////////////////////////


  /// (I.)   lifetime -= 1  and deletes all particles with lifetime < 0;

/*virtual*/
void
ParticleHandler::handleLifeTimes(float steps)
{
  // get Iterators
  particleIterator theParticle    = _particleList.begin();
  particleIterator myEndIterator  = _particleList.end();

  for ( ; theParticle != myEndIterator;)
  {

//    if ((*theParticle)->delayTime != 0)
//    {
//      --(*theParticle)->delayTime;
//    }


    if ((*theParticle)->lifetime < 0 )
    {
       delete (*theParticle);
       theParticle = _particleList.erase(theParticle);
    }
    else
    {
      (*theParticle)->lifetime -= steps;
      ++theParticle;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////


  /// (II.)  move your particles

/*virtual*/
void
ParticleHandler::frameStep(float steps)
{



}


///////////////////////////////////////////////////////////////////////////////


  /// (III.)  draw the particles

/*virtual*/
void
ParticleHandler::draw()
{



}


///////////////////////////////////////////////////////////////////////////////


  /// ...

void
ParticleHandler::clear()
{
  particleConstIterator myIterator    = _particleList.begin();
  particleConstIterator myEndIterator = _particleList.end();

  for ( ; myIterator != myEndIterator; ++myIterator)
  {
    Particle* temp = (*myIterator);
    delete temp;
  }
  _particleList.clear();
}


///////////////////////////////////////////////////////////////////////////////


  /// sort the particles by distance to a point

///*virtual*/
//bool
//ParticleHandler::sortByDistance(const gloost::Point3& cameraPoint)
//{
//  _cameraPosition = cameraPoint;
//  std::sort(_particleList.begin(), _particleList.end(), distCompareFunk);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//
//
///*virtual*/
//bool
//ParticleHandler::distCompareFunk(Particle* left, Particle* right)
//{
//  float distL = (cameraPoint - left.position).length2();
//  float distR = (cameraPoint - right.position).length2();
//
//  return distL < distR;
//}

///////////////////////////////////////////////////////////////////////////////


  /// return number of particles

int
ParticleHandler::size() const
{
  return _particleList.size();
}


///////////////////////////////////////////////////////////////////////////////


 /// get List begin Iterator

ParticleHandler::particleIterator
ParticleHandler::getParticlesBegin()
{
  return _particleList.begin();
}


///////////////////////////////////////////////////////////////////////////////


 /// get List end Iterator

ParticleHandler::particleIterator
ParticleHandler::getParticlesEnd()
{
  return _particleList.end();
}


///////////////////////////////////////////////////////////////////////////////


 /// remove one entry

void
ParticleHandler::remove(ParticleHandler::particleIterator it)
{
  Particle* temp = (*it);

  if (temp)
  {
    temp->lifetime = 0;
  }

}


///////////////////////////////////////////////////////////////////////////////



} // /namespace gloost

