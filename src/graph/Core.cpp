
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

            gloost is being created by Felix Wei�ig and Stephan Beck

     Felix Wei�ig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#include <graph/Core.h>
#include <graph/Action.h>


namespace gloost
{


////////////////////////////////////////////////////////////////////////////////


 /// class constructor

Core::Core(unsigned int typeId):
  SharedResource(),
  _typeId(typeId),
  _disabled(false)
{

}


////////////////////////////////////////////////////////////////////////////////


 /// class destructor

Core::~Core()
{

}


////////////////////////////////////////////////////////////////////////////////


 /// returns the type id of this core

unsigned int
Core::getType()
{
	return _typeId;
}


////////////////////////////////////////////////////////////////////////////////


void
Core::setEnabled(bool enabled)
{
	_disabled = !enabled;
}


////////////////////////////////////////////////////////////////////////////////


bool
Core::isEnabled()
{
	return !_disabled;
}


////////////////////////////////////////////////////////////////////////////////

} // namespace gloost
