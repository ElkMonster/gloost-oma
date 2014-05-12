

#ifndef H_GLOOST_GLOBALPROPERTIES
#define H_GLOOST_GLOBALPROPERTIES






/// gloost system includes
#include <gloostConfig.h>
#include <PropertySet.h>


/// cpp includes
#include <string>



namespace gloost
{


  //  A PropertySet as singelton for application wide variables and configurations

class GlobalProperties: public PropertySet
{
	public:

	  // returns an instance of this class
	  static GlobalProperties* get();

    // class destructor
	  virtual ~GlobalProperties();


//    GlobalProperties();
//    GlobalProperties(const PropertySet& propSet);
//    GlobalProperties(const std::string& xmlFilePath);

	private:


    // class constructor
    GlobalProperties();


    static GlobalProperties* _theInstance;

};


} // namespace gloost


#endif // H_GLOOST_GLOBALPROPERTIES


