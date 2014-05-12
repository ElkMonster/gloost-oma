
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



#ifndef GLOOST_MATRIXCORE_H
#define GLOOST_MATRIXCORE_H



/// gloost includes
#include <graph/Core.h>

#include <Vector3.h>
#include <Matrix.h>


/// cpp includes


namespace gloost
{


class Action;


/// MatrixCore for transformations

class MatrixCore : public Core
{
	public:

		// class constructor
		MatrixCore();

		// class constructor
		MatrixCore(const Matrix& matrix);


		~MatrixCore();



		/* virtual */ void enterCore (const Action* action);
		/* virtual */ void exitCore  (const Action* action);


    /// set the matrix of this MatrixCore
		void setMatrix (const Matrix& matrix /*, bool threadsafe = true*/);


		/// returns the matrix of this MatrixCore
		const Matrix&  getMatrix () const;
		/// returns the matrix of this MatrixCore
    Matrix&  getMatrix ();


  private:

    Matrix _matrix;
};


} // namespace gloost


#endif // GLOOST_MATRIXCORE_H
