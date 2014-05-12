
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
#include <graph/MatrixCore.h>
#include <graph/Action.h>

//#include <changeListManager.h>



/// cpp includes
#include <GL/glew.h>



namespace gloost
{


////////////////////////////////////////////////////////////////////////////////


  ///

// class constructor
MatrixCore::MatrixCore():
  Core(GLOOST_CORE_MATRIX),
  _matrix()
{
   _matrix.setIdentity();
}

////////////////////////////////////////////////////////////////////////////////


  ///

MatrixCore::MatrixCore(const Matrix& matrix):
  Core(GLOOST_CORE_MATRIX),
  _matrix(matrix)
{
  ///
}


////////////////////////////////////////////////////////////////////////////////


  ///

MatrixCore::~MatrixCore()
{

}


////////////////////////////////////////////////////////////////////////////////


  ///

/* virtual */
void
MatrixCore::enterCore (const Action* action)
{
  glPushMatrix();
    gloostMultMatrix(_matrix.data()); /// this->transform();
}


////////////////////////////////////////////////////////////////////////////////


  ///

/* virtual */
void
MatrixCore::exitCore (const Action* action)
{
  glPopMatrix();
}


////////////////////////////////////////////////////////////////////////////////


  ///

void
MatrixCore::setMatrix(const Matrix& matrix /*, bool threadsafe*/)
{
//  if(threadsafe)
//  {
    _matrix = matrix;
//  }
//  else
//  {
//    changeListManager::the()->setMatrix(this, m);
//  }
}


////////////////////////////////////////////////////////////////////////////////


  ///

const Matrix&
MatrixCore::getMatrix () const
{
  return _matrix;
}


////////////////////////////////////////////////////////////////////////////////


  ///

Matrix&
MatrixCore::getMatrix ()
{
  return _matrix;
}


////////////////////////////////////////////////////////////////////////////////


} // namespace gloost

