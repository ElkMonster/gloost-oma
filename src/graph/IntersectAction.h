
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



#ifndef GLOOST_INTERSECTACTION_H
#define GLOOST_INTERSECTACTION_H



#include <graph/Node.h>
#include <graph/Action.h>

#include <Ray.h>

#include <iostream>


namespace gloost
{


 /// Intersect Action

class IntersectAction: public Action
{

	public:
		/// class constructor
		IntersectAction();

		/// class destructor
		~IntersectAction();

    /// start intersect traversel
    /* virtual */ bool start (Node* startNode, Ray& pickRayFromCamera);


		Node* getHitNode() const;
		const Ray getHitRay() const;


		/// reset intersect status
		void reset();



	private:

    bool intersect(Node *node, Ray& ray);

    Node* _hitNode;
    Ray   _hitRay;




};


} // namespace GG


#endif // GG_INTERSECTACTION_H

