
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
#include <gloostConfig.h>
#include <TextureAtlas.h>
#include <TextureManager.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class TextureAtlas

  \brief Stores multiple Textures in one big Texture and provides TexCoords for the areas

  \author Felix Weiszig
  \date   Juli 2010
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

TextureAtlas::TextureAtlas():
    _tilesTexcoords(),
    _uniqueIdCounter(0),
    _atlasTextureId(0),
    _atlasTexture(gloost::TextureManager::getInstance()->getTextureReference(0))
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

TextureAtlas::~TextureAtlas()
{
	// insert your code here
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief creates a texture for the atlas
  \param ...
  \remarks ...
*/

void
TextureAtlas::createAtlasTexture(unsigned int width,
                                 unsigned int height,
                                 unsigned int target,
                                 unsigned int internalFormat,
                                 unsigned int pixelFormat,
                                 unsigned int pixelType)
{
  gloost::TextureManager* texManager = gloost::TextureManager::getInstance();


  _atlasTexture = new Texture( width,
                               height,
                               target,
                               internalFormat,
                               pixelFormat,
                               pixelType );


  _atlasTextureId = texManager->addTexture(_atlasTexture);

//  _atlasTexture->setTexParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  _atlasTexture->setTexParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  _atlasTexture->setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  _atlasTexture->setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  _atlasTexture->enableMipmaps(true);


}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief copys the pixel of an texture to the atlas, returns a id for the texcoords
  \param textureId a texture ID within the TextureManager
  \param positionX
  \param positionY
  \remarks Pixelformat and type of the texture has to match to the atlas texture
*/

unsigned int
TextureAtlas::createTileFromTexture( unsigned int textureId,
                                     unsigned int positionX,
                                     unsigned int positionY)
{

  if (!_atlasTexture)
  {
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl;
    std::cout << std::endl << "ERROR in TextureAtlas::createTileFromTexture():";
		std::cout << std::endl << "         Atlas texture is not ready.";
		std::cout << std::endl << "         Use TextureAtlas::createAtlasTexture(...) first, to create";
		std::cout << std::endl << "         one.";
		std::flush(std::cout);
#endif
    return 0;

  }

  _atlasTexture->bind();

  Texture* tile = TextureManager::getInstance()->getTextureWithoutRefcount(textureId);

  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  positionX,
                  positionY,
                  tile->getWidth(),
                  tile->getHeight(),
                  tile->getPixelFormat(),
                  tile->getPixelType(),
                  tile->getPixels());


  float normX = 1.0/_atlasTexture->getWidth();
  float normY = 1.0/_atlasTexture->getHeight();


  vec4 texCoords(positionX*normX,
                 (positionX+tile->getWidth())*normX,
                 positionY*normY,
                 (positionY+tile->getHeight())*normY);


  int id = _uniqueIdCounter;

  _tilesTexcoords[id] = texCoords;

  ++_uniqueIdCounter;

  return id;

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief ...
  \param ...
  \remarks ...
*/

unsigned int
TextureAtlas::getAtlasTextureId() const
{
  return _atlasTextureId;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief ...
  \param ...
  \remarks ...
*/

Texture*
TextureAtlas::getAtlasTexture()
{
  return _atlasTexture;
}


////////////////////////////////////////////////////////////////////////////////


 ///

unsigned int
TextureAtlas::getNumEntries() const
{
  return _tilesTexcoords.size();
}




////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


