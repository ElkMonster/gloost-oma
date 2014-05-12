
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



#ifndef GLOOST_SETTRAVMASK_ACTION_H
#define GLOOST_SETTRAVMASK_ACTION_H



/// gloost system includes
#include <graph/Node.h>
#include <graph/Action.h>
#include <Camera.h>



/// cpp includes
#include <iostream>



namespace gloost
{


 /// Traverser, sets Nodes TravMasks to a defined value


class SetTravMaskAction: public Action
{

	public:
		/// class constructor
		SetTravMaskAction();

		/// class constructor
		SetTravMaskAction(int contextId);


		/// class destructor
		~SetTravMaskAction();


    /// start traversal
    void startSetFlags(Node* startNode, bool value);

    /// start traversal
//    void startCullNothing (Node* startNode);



	private:


    Camera* _currentCamera;


    void setFlags (Node* startNode, bool value);
//    void cullNothing (Node *myNode);



};


} // namespace gloost


#endif // GLOOST_SETTRAVMASK_ACTION_H

