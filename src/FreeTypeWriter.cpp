
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



/// gloost system includes
#include <FreeTypeWriter.h>
#include <TextureManager.h>
#include <TileSet.h>
#include <gloostRenderGoodies.h>


//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>


/// cpp includes
#include <string>
#include <iostream>


// Using the STL exception library increases the
// chances that someone else using our code will corretly
// catch any exceptions that we throw.
#include <stdexcept>



namespace gloost
{

/**
  \class   FreeTypeWriter

  \brief   Writes Text on screen using ttf fonts (uses GNU's freetype)

  \author  Felix Weiszig
  \date    May 2011
  \remarks Much of the code was taken from Nehe lesson 43, written by Jeff Molofee
           This is his original message:
           <i>
             This code was created by Jeff Molofee '99
             (ported to Linux/SDL by Ti Leggett '01)

             If you've found this code useful, please let me know.

             Visit Jeff at http://nehe.gamedev.net/

             or for port-specific comments, questions, bugreports etc.
             email to leggett@eecs.tulane.edu
           </i>
*/


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

FreeTypeWriter::FreeTypeWriter(const std::string& fontPath,
                               unsigned charHeight,
                               bool     antialiased,
                               unsigned alignModeH,
                               float    charDistance,
                               float    lineDistance):
  _fontPath(fontPath),
  _fontHeight(charHeight),
  _antialiased(antialiased),
  _fontAtlas(new TileSet()),
  _glyphSpecs(),
  _writePos(),
  _glScale(1.0),
  _charDistance(charDistance),
  _lineDistance(lineDistance),
  _alignModeH(alignModeH)
{

  FT_Library library;

  // Create and initilize a freetype font library.
  if (FT_Init_FreeType( &library ))
  {
    throw std::runtime_error("FT_Init_FreeType failed");
  }


  //The object in which Freetype holds information on a given
  //font is called a "face".
  FT_Face face;

  //This is where we load in the font information from the file.
  //Of all the places where the code might die, this is the most likely,
  //as FT_New_Face will die if the font file does not exist or is somehow broken.
  if (FT_New_Face( library, fontPath.c_str(), 0, &face ))
  {
    throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
  }

  //For some twisted reason, Freetype measures font size
  //in terms of 1/64ths of pixels.  Thus, to make a font
  //h pixels high, we need to request a size of h*64.
  FT_Set_Char_Size( face, charHeight * 64, charHeight * 64, 96, 96);

  std::vector<unsigned> texIds(128, 0);
  _glyphSpecs = std::vector<glyphSpec>(128, glyphSpec());
  int maxWidth  = 0;
  int maxHeight = 0;

  //This is where we actually create each of the fonts display lists.
  for(unsigned char ch=0; ch<128; ch++)
  {
    // The first thing we do is get FreeType to render our character
    // into a bitmap.  This actually requires a couple of FreeType commands:

    // Load the Glyph for our character.
    if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
      throw std::runtime_error("FT_Load_Glyph failed");

    // Move the face's glyph into a Glyph object.
    FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
      throw std::runtime_error("FT_Get_Glyph failed");

    // Convert the glyph to a bitmap.

    if (antialiased)
    {
      FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    }
    else
    {
      FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_MONO, 0, 1 );
    }

    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

    //This reference will make accessing the bitmap easier
    FT_Bitmap& bitmap=bitmap_glyph->bitmap;

    // Use our helper function to get the widths of
    // the bitmap data that we will need in order to create
    // our texture.
    int width  = bitmap.width;
    int height = bitmap.rows;
    maxWidth  = gloost::max(maxWidth, width);
    maxHeight = gloost::max(maxHeight, height);

    // store the glyphs attributes to use them later while rendering
    _glyphSpecs[ch]._width      = width;
    _glyphSpecs[ch]._height     = height;
    _glyphSpecs[ch]._leftOffset = bitmap_glyph->left;
    _glyphSpecs[ch]._topOffset  = bitmap_glyph->top;


    // Allocate memory for the texture data.
    unsigned bufferSize    =  width * height * 2;
    GLfloat* expanded_data = new GLfloat[bufferSize];

    // Here we fill in the data for the expanded bitmap.
    // Notice that we are using two channel bitmap (one for
    // luminocity and one for alpha), but we assign
    // both luminocity and alpha to the value that we
    // find in the FreeType bitmap.
    // We use the ?: operator so that value which we use
    // will be 0 if we are in the padding zone, and whatever
    // is the the Freetype bitmap otherwise.

    if (antialiased)
    {
      for(int y=0; y != height; ++y)
      {
        for(int x=0; x != width; ++x)
        {
          {
            int readIndex  = (x + y*width);
            // invert y
            int writeIndex = (x + (height-y-1) * width) * 2;

  //          std::cerr << std::endl << "writeIndex: " << writeIndex;

            expanded_data[writeIndex] = 1.0;
            expanded_data[writeIndex+1] = bitmap.buffer[readIndex]/255.0;
          }
        }
      }

    }
    else
    {
      //-----------------------------------
      // true type packs monochrome info in a
      // 1-bit format, hella funky
      // here we unpack it:
      unsigned char *src = bitmap.buffer;
      for(int y=0; y != bitmap.rows; ++y)
      {

        int yi = (int)bitmap.rows-y-1;

        unsigned char b = 0;
        unsigned char *bptr = src;
        for(int x=0; x != bitmap.width ; ++x)
        {

          int index = 2*((x)+(yi)*width);

          expanded_data[index] = 1;

          if (x%8==0)
          {
            b = (*bptr++);
          }

          expanded_data[index + 1] = b&0x80 ? 1 : 0;
          b <<= 1;
        }
        src += bitmap.pitch;
      }
      //-----------------------------------
    }





    // Now we just setup some texture paramaters.

    //Here we actually create the texture itself, notice
    //that we are using GL_LUMINANCE_ALPHA to indicate that
    //we are using 2 channel data.

//    if (bufferSize)
    {
      gloost::Texture* glyphTexture = new gloost::Texture(width,
                                                          height,
                                                          1,
                                                          (unsigned char*)expanded_data,
                                                          8,
                                                          GL_TEXTURE_2D,
                                                          GL_LUMINANCE_ALPHA,
                                                          GL_LUMINANCE_ALPHA,
                                                          GL_FLOAT);
      glyphTexture->takeReference();

      texIds[ch] = gloost::TextureManager::getInstance()->addTexture(glyphTexture);
    }
//    else
//    {
//      texIds[ch] = 0;
//    }
  }



  for (unsigned int ch=0; ch!=_glyphSpecs.size(); ++ch)
  {

    if (_glyphSpecs[ch]._width == 0)
    {
      _glyphSpecs[ch]._width = maxWidth*0.333;
    }

//    std::cerr << std::endl << "char: " << (int)ch << ": " << (char) ch;
//    std::cerr << std::endl << "      " << _glyphSpecs[ch].width << "x " << _glyphSpecs[ch].height;
//    std::cerr << std::endl << "      " << _glyphSpecs[ch].leftOffset << ", " << _glyphSpecs[ch].topOffset;
//    std::cerr << std::endl;
  }


  int numTilesH = 16;
  int numTilesV = 8;


  unsigned atlasBufferSize = maxWidth*numTilesH*maxHeight*numTilesV*2;
  float*   atlasBuffer     = new GLfloat[atlasBufferSize];

  for (unsigned int i=0; i!=atlasBufferSize; ++i)
  {
    atlasBuffer[i] = 0;
  }

  gloost::Texture* atlasTexture = new gloost::Texture(maxWidth*numTilesH,
                                                      maxHeight*numTilesV,
                                                      1,
                                                      (unsigned char*)atlasBuffer,
                                                      8,
                                                      GL_TEXTURE_2D,
                                                      GL_LUMINANCE_ALPHA,
                                                      GL_LUMINANCE_ALPHA,
                                                      GL_FLOAT);
  atlasTexture->takeReference();

  atlasTexture->setTexParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  atlasTexture->setTexParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//  atlasTexture->setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  atlasTexture->setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned atlasTextureId = gloost::TextureManager::getInstance()->addTexture(atlasTexture);

  _fontAtlas->loadFromTexture(atlasTextureId, numTilesH, numTilesV);


  /// copy all tiles into one tile texture
  int x = 0;
  int y = 0;
  for (unsigned int i=0; i!=texIds.size(); ++i)
  {
     _fontAtlas->createTileFromTexture(texIds[i],
                                       x*maxWidth,
                                       y*maxHeight);

    ++x;

    if (x == (int)(_fontAtlas->getNumTilesH()))
    {
      x = 0;
      ++y;
    }

    /// drop refrence of this single tile because it is no longer needed
    gloost::TextureManager::getInstance()->dropReference(texIds[i]);
  }


//  std::cerr << std::endl;
//  std::cerr << std::endl << "maxWidth:  " << maxWidth;
//  std::cerr << std::endl << "maxHeight: " << maxHeight;
//  std::cerr << std::endl << "----------------------";



  //We don't need the face information now that the display
  //lists have been created, so we free the assosiated resources.
  FT_Done_Face(face);

  //Ditto for the library.
//  FT_Done_FreeType(library);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

FreeTypeWriter::~FreeTypeWriter()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the font atlas/tileset
  \param   ...
  \remarks ...
*/

TileSet*
FreeTypeWriter::getFontTileSet()
{
  return _fontAtlas;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a container with the left and top bearings and horizontal and vertical size of each char
  \param   ...
  \remarks ...
*/

std::vector<FreeTypeWriter::glyphSpec>&
FreeTypeWriter::getGlyphSpecs()
{
  return _glyphSpecs;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a container with the left and top bearings and horizontal and vertical size of each char
  \param   ...
  \remarks ...
*/

const std::vector<FreeTypeWriter::glyphSpec>&
FreeTypeWriter::getGlyphSpecs() const
{
  return _glyphSpecs;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   binds the font atlas and setups writing
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::beginText()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0);


  glEnable(GL_TEXTURE_2D);
  _fontAtlas->getAtlasTexture()->bind();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   ends the text writing
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::endText()
{
  _fontAtlas->getAtlasTexture()->unbind();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes a line of text
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::writeLine(float x, float y, const std::string& text)
{
  _writePos = gloost::Point3(x,y,0.0f);
  write(text);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes a line of text
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::writeLine(float xOffset, const std::string& text)
{
  nextLine();
  _writePos[0] += xOffset;

  write(text);

  _writePos[0] -= xOffset;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes a line of text
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::writeLine(const std::string& text)
{
  nextLine();
  write(text);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   skips one line
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::nextLine()
{
  float _lineDist = 1.0;
  _writePos[1] -= _fontAtlas->getTileHeight() + _lineDist;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief       returns the length of a line for current configuration
  \param   ...
  \remarks ...
*/

float
FreeTypeWriter::getLineLength(const std::string& text) const
{
  float posX = 0;

  const char* chars = text.c_str();

  unsigned index = 0;
  for (unsigned int c=0; c!=text.length(); ++c)
  {
    index = chars[c];

    if (index > _fontAtlas->getNumEntries())
    {
      index = 32;
    }

    const glyphSpec& specs = getGlyphSpecs()[index];

    posX += (specs._width + specs._leftOffset + _charDistance)*_glScale;
  }

  return posX;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief       // writes a line of text
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::write(const std::string& text)
{
  Point3 pos = _writePos;

  if (_alignModeH != GLOOST_FREETYPEWRITER_ALIGN_LEFT)
  {
    float lineLength = getLineLength(text);

    if (_alignModeH == GLOOST_FREETYPEWRITER_ALIGN_CENTER)
    {
      pos[0] -= lineLength*0.5;
    }
    else if (_alignModeH == GLOOST_FREETYPEWRITER_ALIGN_RIGHT)
    {
      pos[0] -= lineLength;
    }
  }

  const char* chars = text.c_str();

  unsigned index = 0;

  for (unsigned int c=0; c!=text.length(); ++c)
  {
    index = chars[c];

    if (index > _fontAtlas->getNumEntries())
    {
      index = 32;
    }

    glyphSpec& specs = getGlyphSpecs()[index];
    glPushMatrix();
    {

      glTranslatef( (int) pos[0] + specs._leftOffset,
                    (int) pos[1] - (specs._height-specs._topOffset)*_glScale, 0.0);

      pos[0] += (specs._width + specs._leftOffset + _charDistance)*_glScale;

      glScalef( specs._width  * _glScale,
                specs._height * _glScale,
                1.0f);
      /// draw some stuff
      gloost::drawQuad(getFontTileSet()->getTexCoordsForFrame(index));
    }
    glPopMatrix();

    ++index;

  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the write position
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::setWritePos(const Point3& pos)
{
  _writePos = pos;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the write position
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::setWritePos(float x, float y)
{
  _writePos[0] = x;
  _writePos[1] = y;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the scaling
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::setScale(float scale)
{
  _glScale = scale;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the horizontal align mode to GLOOST_FREETYPEWRITER_ALIGN_LEFT,
           GLOOST_FREETYPEWRITER_ALIGN_RIGHT or GLOOST_FREETYPEWRITER_ALIGN_CENTER
  \param   ...
  \remarks ...
*/

void
FreeTypeWriter::setAlignModeH(unsigned alignModeH)
{
  _alignModeH = alignModeH;
}


////////////////////////////////////////////////////////////////////////////////


} // namespace gloost


