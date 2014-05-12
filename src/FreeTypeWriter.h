
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

            gloost is being created by Felix Weißig and Stephan Beck

     Felix Weißig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef H_GLOOST_FREETYPEWRITER
#define H_GLOOST_FREETYPEWRITER



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <ft2build.h>
#include <freetype/freetype.h>



#define GLOOST_FREETYPEWRITER_ALIGN_LEFT   0
#define GLOOST_FREETYPEWRITER_ALIGN_RIGHT  1

#define GLOOST_FREETYPEWRITER_ALIGN_BOTTOM 0
#define GLOOST_FREETYPEWRITER_ALIGN_TOP    1

#define GLOOST_FREETYPEWRITER_ALIGN_CENTER 2



namespace gloost
{


  class TileSet;



  //  Writes Text on screen using ttf fonts (uses GNU's freetype)

class FreeTypeWriter
{
	public:


	  // margin
	  struct glyphSpec
	  {
	    glyphSpec()
	    {
	      _leftOffset = 0;
	      _topOffset  = 0;
	      _width      = 0;
	      _height     = 0;
	    }

	    glyphSpec(int leftOffset, int topOffset, int width, int height)
	    {
	      _leftOffset = leftOffset;
	      _topOffset  = topOffset;
	      _width      = width;
	      _height     = height;
	    }

      int _leftOffset;
      int _topOffset;
      int _width;
      int _height;
	  };


    // class constructor
    FreeTypeWriter(const std::string& fontPath,
                   unsigned charHeight,
                   bool antialiased    = true,
                   unsigned alignModeH = GLOOST_FREETYPEWRITER_ALIGN_LEFT,
                   float charDistance  = 1.0f,
                   float lineDistance  = 1.0f);

    // class destructor
	  ~FreeTypeWriter();



	  // returns the font atlas/tileset
	  TileSet* getFontTileSet();

	  // returns a container with the left and top bearings and horizontal and vertical size of each char
	  std::vector<glyphSpec>& getGlyphSpecs();
	  const std::vector<glyphSpec>& getGlyphSpecs() const;



    // binds the font atlas and setups writing
    void beginText();

    // ends the text writing
    void endText();

    // writes a line of text
    void writeLine(float x, float y, const std::string& text);
    void writeLine(float xOffset, const std::string& text);
    void writeLine(const std::string& text);

    // skips a line
    void nextLine();


    // returns the length of a line for current configuration
    float getLineLength(const std::string& text) const;


    // sets the write position
    void setWritePos(const Point3& pos);
    void setWritePos(float x, float y);


    // sets the scaling
    void setScale(float scale);

    // sets the horizontal align mode to GLOOST_FREETYPEWRITER_ALIGN_LEFT, GLOOST_FREETYPEWRITER_ALIGN_RIGHT or GLOOST_FREETYPEWRITER_ALIGN_CENTER
    void setAlignModeH(unsigned alignModeH);



	private:

   std::string _fontPath;
   unsigned    _fontHeight;
   bool        _antialiased;

   TileSet*               _fontAtlas;
   std::vector<glyphSpec> _glyphSpecs;

   gloost::Point3 _writePos;
   float          _glScale;
   float          _charDistance;
   float          _lineDistance;

   unsigned       _alignModeH;





   void write (const std::string& text);






};


} // namespace gloost


#endif // H_GLOOST_FREETYPEWRITER


