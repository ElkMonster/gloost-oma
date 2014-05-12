
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



#ifndef GLOOST_PAD_H
#define GLOOST_PAD_H



/// gloost includes
#include <TextureText.h>
#include <TextLog.h>
#include <Mouse.h>
#include <Vector2.h>


#include <gui/Widget.h>


/// cpp includes
#include <string>



namespace gloost
{


  /// (Gui widget) A XY-Pad to set two values at once

class Pad: public Widget
{
	public:

    /// class constructor
    Pad(std::string name,
         std::string title,
         gloost::Vector2 position,
         gloost::Vector2 size = gloost::Vector2(100.0f, 18.0f),
         float minValueX = 0.0f,
         float maxvalueX = 1.0f,
         float defaultValueX = 0.0f,
         float minValueY = 0.0f,
         float maxvalueY = 1.0f,
         float defaultValueY = 0.0f,
         std::string valueType = "float");

    /// load a xml file
    Pad(const std::string& xmlFilePath);

    /// class destructor
	  ~Pad();



    /// loads all necessary resources for this node
    void loadResources();


	  /// render the screen
    void onDraw();

    ///
    /*virtual*/ void onEnterFrame();


    /// recalc the scaled value
    void normalizedToValue();

    /// recalc the normalized value from value
    void valueToNormalized();

	private:

	  gloost::TextureText* _textMaker;
};


} // namespace gloost


#endif // GLOOST_PAD_H







