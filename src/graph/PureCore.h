
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



#ifndef GLOOST_PURECORE_H
#define GLOOST_PURECORE_H


#include <graph/Core.h>


namespace gloost
{


class Action;
class Material;


 /// This is just a emty core with no functionality at all

class PureCore : public Core
{

	public:

		 PureCore ();
		~PureCore ();


		/* virtual */ void enterCore (const Action* action);
		/* virtual */ void exitCore  (const Action* action);



  private:
    ///s
};


} // namespace gloost

#endif // GLOOST_PURECORE_H
