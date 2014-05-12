
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



#ifndef GLOOST_TEXTINPUT_H
#define GLOOST_TEXTINPUT_H



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


  /// (Gui widget) Text input field

class TextInput: public Widget
{
	public:

    /// class constructor
    TextInput(std::string name,
              std::string title,
              const std::string& defaultText,
              gloost::Vector2 position,
              gloost::Vector2 size = gloost::Vector2(14.0f, 14.0f));

    /// class destructor
	  ~TextInput();



    /// loads all necessary resources for this node
    void loadResources();


	  /// render the screen
    void onDraw();

    ///
    /*virtual*/ void onEnterFrame();


    ///
//    /*virtual*/ void onMouseUp();
    /*virtual*/ void onMouseDown();
    /*virtual*/ void onMouseUpOutside();

    /*virtual*/ bool onHandleKey(const unsigned char& asciiChar);

	private:

	  gloost::TextureText* _textMaker;
};


} // namespace gloost


#endif // GLOOST_BUTTON_H







