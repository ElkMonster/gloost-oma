
/// vxfv system includes
#include <GlobalProperties.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class GlobalProperties

  \brief A PropertySet as singelton for application wide variables and configurations

  \author Felix Weiszig
  \date   May 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/*static*/ GlobalProperties* GlobalProperties::_theInstance = 0;


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

GlobalProperties::GlobalProperties():
  PropertySet()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

GlobalProperties::~GlobalProperties()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////

/**
  \brief returns an instance of this class
  \remarks ...
*/

/*static*/
GlobalProperties* GlobalProperties::get()
{
  if (!_theInstance)
  {
    _theInstance = new GlobalProperties();
  }

  return _theInstance;
}


////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


