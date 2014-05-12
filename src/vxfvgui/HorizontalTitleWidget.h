

#ifndef H_VXFV_HORIZONTALTITLEWIDGET
#define H_VXFV_HORIZONTALLINE



/// vxfv includes
#include <vxfvgui/VxfvWidget.h>


/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <list>



namespace gloost
{


  class Mouse;


  //  A button widget

class HorizontalTitleWidget: public VxfvWidget
{
	public:

    // class constructor
    HorizontalTitleWidget(VxfvGui* gui);

    // class destructor
	  virtual ~HorizontalTitleWidget();


    virtual void onInitWidget();
    virtual void onUpdateMesh();

    virtual void onEnterFrame();
    virtual void onExitFrame();


    virtual void onDraw();


	private:





};


} // namespace gloost


#endif // H_VXFV_HORIZONTALTITLEWIDGET


