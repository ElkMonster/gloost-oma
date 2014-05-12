
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



#ifndef GLOOST_GLUTGOODIES_H
#define GLOOST_GLUTGOODIES_H



/// cpp includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>



namespace gloost
{



///////////////////////////////////////////////////////////////////////////////


  /// render a string using glut

void renderBitmapString( float x, float y, float z, std::string line, void *font = GLUT_BITMAP_HELVETICA_12)
{

  const char* characters = line.c_str();
  glRasterPos3f(x,y,z);

  for (const char* c = characters; *c != '\0'; c++)
  {
    glutBitmapCharacter(font, *c);
  }
}

///////////////////////////////////////////////////////////////////////////////






}  // namespace gloost


#endif // #ifndef GLOOST_GLUTGOODIES_H

