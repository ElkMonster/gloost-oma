
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



#ifndef H_GLOOST_TEXTUREATLAS
#define H_GLOOST_TEXTUREATLAS



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>
#include <Texture.h>


/// cpp includes
#include <string>



namespace gloost
{


  //  Stores multiple Textures in one big Texture and provides TexCoords for the areas

class TextureAtlas
{
	public:

    // class constructor
    TextureAtlas();

    // class destructor
	  virtual ~TextureAtlas();


    // creates a texture for the atlas
	  void createAtlasTexture( unsigned int width,
                             unsigned int height,
                             unsigned int target,
                             unsigned int internalFormat,
                             unsigned int pixelFormat,
                             unsigned int pixelType);



    /* copys the pixel of an texture to the atlas, returns a id for the texcoords
       Pixelformat and type of the texture has to match to the atlas texture */
    unsigned int createTileFromTexture(unsigned int textureId,
                                       unsigned int positionX,
                                       unsigned int positionY);



    ///
    unsigned int getAtlasTextureId() const;

    ///
    Texture* getAtlasTexture();


    ///
    unsigned int getNumEntries() const;


	protected:


	  std::map<unsigned int, gloost::vec4> _tilesTexcoords;

	  unsigned int _uniqueIdCounter;

    unsigned int _atlasTextureId;
	  Texture*     _atlasTexture;
};


} // namespace gloost


#endif // H_GLOOST_TEXTUREATLAS



