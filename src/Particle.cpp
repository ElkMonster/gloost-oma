
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



/// objfile system includes
#include <Particle.h>



/// cpp includes
#include <GL/gl.h>
#include <GL/glut.h>



namespace gloost
{

///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Particle::Particle()
{
  lifetime  = -1;
  weight    = 1.0;
  bouncynes = 1.0;
  size      = 1.0;
  index     = 0;
}


///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Particle::~Particle()
{

}


///////////////////////////////////////////////////////////////////////////////


//  /// draws the object
//
//void
//Particle::draw_raw()
//{
//
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//
//
//  /// draws the object with UV coordinates for color to pick
//
//void
//Particle::draw_tangent()
//{
//
//}


///////////////////////////////////////////////////////////////////////////////


  /// build a display list from the obj file

//bool
//Particle::buildLists(const char* objfile, GLuint* listraw, GLuint* list)
//{
//
//
//
//}






} // namespace gloost


