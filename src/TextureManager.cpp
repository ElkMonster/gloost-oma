
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
/// gloost system includes
#include <TextureManager.h>
/// cpp includes
#include <iostream>
#include <vector>
namespace gloost
{
/**
 \class TextureManager
 \brief Texture container and factory. Use this class to create, manage and share your Texture
         resources within your application.
 \author Felix Weiszig
 \date   December 2009
 \remarks Consult the step_04_Textures_and_TextureManager
           tutorial located in <i><gloost>/tutorials/essentials/</i> to learn more.
           <br>This class is a singleton. To get a reference to the instance write:
           \code
           gloost::TextureManager* texManager = gloost::TextureManager::getInstance();
           \endcode
           To load a texture write:
           \code
           // you can do it like this
           unsigned int texId = texManager->createTexture("Image.png");
           // or like this
           unsigned int texId = gloost::TextureManager::getInstance()->createTexture("Image.png");
           \endcode
           To get the Texture instance for the id try:
           \code
           // This will increment the reference counter
           gloost::Texture* tex = texManager->getTextureReference(texId);
           // This will NOT increment the reference counter
           gloost::Texture* tex = texManager->getTextureWithoutRefcount(texId);
           \endcode
*/



/*static*/  TextureManager* TextureManager::_theinstance = 0;



///////////////////////////////////////////////////////////////////////////////


/**
 \brief Class constructor
*/

TextureManager::TextureManager():
    _textures(),
    _shareMap(),
    _assignMap(),
    _idMutex()
{
   // create a default texture at id 0
   Texture* defaultTexture = new Texture(512,
                                         512,
                                         16,
                                         GL_TEXTURE_2D,
                                         GL_RGBA,
                                         GL_RGBA,
                                         GL_FLOAT);

  addTexture(defaultTexture);
}

///////////////////////////////////////////////////////////////////////////////


  /// class destructor

TextureManager::~TextureManager()
{
  getTextureWithoutRefcount(0)->dropReference();
  cleanUp();
}


///////////////////////////////////////////////////////////////////////////////


  /// get an instance to the TextureManager

TextureManager*
TextureManager::getInstance()
{
  if(!_theinstance)
  {
    _theinstance = new TextureManager();
  }
  return _theinstance;
}


///////////////////////////////////////////////////////////////////////////////


  /// get an instance to the TextureManager

TextureManager*
TextureManager::get()
{
  if(!_theinstance)
  {
    _theinstance = new TextureManager();
  }
  return _theinstance;
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// Creates empty Texture with given width and height and returns a unique id (refCount +)

//unsigned int
//TextureManager::createTexture(unsigned int width, unsigned int height)
//{
//  // generate a new texture
//  _textures[_idCounter] = new Texture(width, height);
//  // increment the refCounter +1
//  _textures[_idCounter]->takeReference();
//  ++_idCounter;
//  return _idCounter-1;
//}


//////////////////////////////////////////////////////////////////////////////////////////


/// returns a new texture id (thread save)

unsigned
TextureManager::getNewTextureId()
{
  boost::mutex::scoped_lock lock(_idMutex);
  static unsigned idCounter = 0;
  ++idCounter;
  return idCounter;
}



//////////////////////////////////////////////////////////////////////////////////////////


		/**
		  Creates empty Texture with specific id object of given width and height
		  This will overwrite existing textures with this id, so don't mess around with this
		  (refCount +)
		**/


unsigned int
TextureManager::createTexture(unsigned int id, unsigned int width, unsigned int height)
{
  // generate a new texture
  _textures[id] = new Texture( 512,
                               512,
                               16,
                               GL_TEXTURE_2D,
                               GL_RGBA,
                               GL_RGBA,
                               GL_FLOAT);
  // increment the refCounter +1
  _textures[id]->takeReference();
  return id;
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// load a texture (automatic configuration of the GL_Texture_2Ds format and type) (tested: jpg, png24, png32)

unsigned int
TextureManager::createTexture(std::string file_name, bool share)
{
  // if this texture is shared we first look in the map if this texture
  // has been allready loaded
  if (share)
  {
      std::map<std::string, unsigned int>::iterator pos = _shareMap.find(file_name);
      if (pos != _shareMap.end())
      {
//#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
//        std::cout<< std::endl;
//        std::cout << std::endl << "Message from TextureManager::createTexture:" ;
//        std::cout<< std::endl << "          Image with filename \"" << file_name << "\" is shared";
//        std::cout<< std::endl << "          ID: " << (*pos).second;
//        std::flush(std::cout);
//#endif
        /// increment the reference counter
        getTextureReference((*pos).second);
        return (*pos).second;
      }
  }
  // we take us a new unique id...
  unsigned int newId = getNewTextureId();
  // generate a new texture
  _textures[newId] = new Texture(file_name);
  // increment the refCounter +1
  _textures[newId]->takeReference();
  // add the texture to the share lookup map
  if (share)
  {
    _textures[newId]->setShared(true);
    _shareMap[file_name] = newId;
  }
  return newId;
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// Add existing Texture to be managed by the TextureManager (refCount +)

unsigned int
TextureManager::addTexture(Texture* texture)
{
  unsigned id = getNewTextureId();
  texture->takeReference();
  _textures[id] = texture;
  return id;
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// removes a texture from the TextureManager

void
TextureManager::removeTexture(unsigned id)
{
  std::map<unsigned int, Texture*>::iterator pos = _textures.find(id);

  if (pos != _textures.end())
  {
    gloost::Texture* texture = (*pos).second;
    _textures.erase(pos);

    if (texture->isShared())
    {
      texture->setShared(false);
      _shareMap.erase(texture->getFileName());
    }
    texture->dropReference();
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// returns reference to gloost::Texture object and increments the reference counter (refCount +)

Texture*
TextureManager::getTextureReference(unsigned int id)
{
  std::map<unsigned int, Texture*>::iterator pos = _textures.find(id);
  if (pos != _textures.end())
  {
    // (refCount +)
    (*pos).second->takeReference();
    return (*pos).second;
  }
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
  std::cout<< std::endl;
  std::cout<< std::endl << "ERROR in TextureManager::getTextureReference():";
  std::cout<< std::endl << "         Could not find existing texture with id = " << id << " !";
  std::cout<< std::endl << "         Will create a BLACK default Texture with size " << 512 << "x" << 512;
  std::cout<< std::endl << "         and the same id you asked for. So your applcation wont crash.";
  std::cout<< std::endl << "         FIX YOUR CODE NOW !!!";
  std::flush(std::cout);
#endif
  /*
    This is buggy! If the id is bigger than _idCounter...
  */
  /// create a help texture
  createTexture(id, 512, 512);
  //_textures[id]->fill(1.0, 0.0, 1.0);
  // (refCount +)
  _textures[id]->takeReference();
  return _textures[id];
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// returns reference to gloost::Texture object WITHOUT increments the reference counter

Texture*
TextureManager::getTextureWithoutRefcount(unsigned int id)
{
  std::map<unsigned int, Texture*>::iterator pos = _textures.find(id);
  if (pos != _textures.end())
  {
    return (*pos).second;
  }
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
  std::cout<< std::endl;
  std::cout<< std::endl << "ERROR in TextureManager::getTextureReference():";
  std::cout<< std::endl << "         Could not find existing texture with id = " << id << " !";
  std::cout<< std::endl << "         You will get the TextureManagers default Texture";
  std::cout<< std::endl << "         so your applcation won't crash.";
  std::cout<< std::endl << "         FIX YOUR CODE NOW !!!";
  std::flush(std::cout);
#endif
  /// create a help texture
  //  createTexture(id, 512, 512);
  // (refCount +)
  _textures[0]->takeReference();
  return _textures[0];
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// drops reference to gloost::Texture object

bool
TextureManager::dropReference(unsigned int id)
{
  std::map<unsigned int, Texture*>::iterator pos = _textures.find(id);
  if (pos != _textures.end())
  {
    if (_textures[id]->getReferenceCount() == 1)
    {
      removeTexture(id);
    }
    else
    {
      _textures[id]->dropReference();
    }
    return 1;
  }

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_WARNINGS
  std::cout<< std::endl;
  std::cout<< std::endl << "Warning from TextureManager::dropReference():";
  std::cout<< std::endl << "             Could not find a texture with id = " << id << "!";
  std::cout<< std::endl;
  std::flush(std::cout);
#endif
  return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////


  /// unloads all textures which are only referenced by the TextureManager

void
TextureManager::cleanUp()
{
#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
  std::cout<< std::endl;
  std::cout<< std::endl << "Message from TextureManager::cleanup():";
  std::cout<< std::endl << "             Removing all Textures with refCount == 0 from gfx-card";
  std::cout<< std::endl << "             and main memory.";
  std::cout<< std::endl;
  std::flush(std::cout);
#endif
  std::map<unsigned int, Texture*>::iterator texIt    = _textures.begin();
  std::map<unsigned int, Texture*>::iterator texEndIt = _textures.end();


  std::vector<unsigned int> idsToBeDeleted;

  for ( ; texIt != texEndIt; ++texIt)
  {
    if ( (*texIt).second->getReferenceCount() == 1 && (*texIt).first != 0)
    {
      idsToBeDeleted.push_back((*texIt).first);
    }
  }

  // remove textures
  for (unsigned int i=0; i!=idsToBeDeleted.size(); ++i)
  {
    removeTexture(idsToBeDeleted[i]);
  }


//#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
//  std::cerr<< std::endl;
//  std::cerr<< std::endl << "Message from TextureManager::cleanUp():";
//  std::cerr<< std::endl << "             Cleanup done... ";
//  std::cerr<< std::endl << "             Following (" << idsToBeDeleted.size() << ") Textures are gone:";
//  for(unsigned int i=0; i!=idsToBeDeleted.size(); ++i)
//  {
//    std::cerr<< std::endl << "                          -> " << idsToBeDeleted[i];
//  }
//  std::cerr<< std::endl;
//  std::cerr<< std::endl << "             Textures left:  " << _textures.size();
//  std::cerr<< std::endl << "             Shared entries: " << _shareMap.size();
//  std::cerr<< std::endl;
//  std::flush(std::cerr);
//#endif
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// returns number of textures within the manager

unsigned int
TextureManager::getSize() const
{
  return _textures.size();
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// prints infos for all textures within the manager

void
TextureManager::printTextureInfo() const
{
  std::map<unsigned int, Texture*>::const_iterator index = _textures.begin();
  std::map<unsigned int, Texture*>::const_iterator end   = _textures.end();
  for ( ; index != end; ++index)
  {
    std::cout << std::endl << (*index).first << " :";
    std::cout << (*(*index).second);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


/* extern */
std::ostream&
operator<< (std::ostream& os, const TextureManager& tm)
{
  os << std::endl << "TextureManager" << std::endl << "{";
  os << std::endl << "    size:    " << tm.getSize();
  os << std::endl;
  tm.printTextureInfo();
  os << std::endl;
  os << std::endl << "} // TextureManager" << std::endl;
  std::flush(os);
  return os;
}


///////////////////////////////////////////////////////////////////////////////


} // namespace gloost
