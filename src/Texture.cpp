
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



/// cpp includes
#include <iostream>



/// gloost system includes
#include <Texture.h>
#include <glErrorUtil.h>
#include <BinaryBundle.h>



namespace gloost
{

///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Texture::Texture(const std::string& fileName):
    MultiGlContext(1),
    _width(1),
    _height(1),
    _depth(1),
    _target(GL_TEXTURE_2D),
    _internalFormat(GL_RGB),
    _pixelFormat(GL_RGB),
    _pixelType(GL_UNSIGNED_BYTE),
    _dirty(GLOOST_BITMASK_ALL_SET),
    _textureUnitIdsForContexts(GLOOST_SYSTEM_NUM_RENDER_CONTEXTS, GL_TEXTURE0),
    _mipmapsEnabled(false),
    _pixelData(0),
    _bytesPerPixel(0),
    _glTexParameters(),
    _texMatrix(),
    _useTextureMatrix(0),
    _shared(0),
    _fileName(fileName)
{

	// Set some default texParameter so you will see something
  setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  setTexParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	Image image(fileName);


	// If the image loaded
	if( image.hasPixels() )
	{
		_width  = image.getWidth();
		_height = image.getHeight();
		_target = GL_TEXTURE_2D;

    _bytesPerPixel = (int)image.getBitsPerPixel()/8;

    _pixelData = new BinaryBundle(image.getPixelData(), _width*_height*_bytesPerPixel);
    _pixelData->takeReference();
    _pixelData->put(image.getPixelData(), _width*_height*_bytesPerPixel);

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
    std::cout << std::endl;
    std::cout << std::endl << "Message from Texture::Texture(std::string) on SharedResource " << getSharedResourceId() << ":";
    std::cout << std::endl << "             Image \"" << fileName << "\" loaded as " << _bytesPerPixel*8 << " bit texture.";
		std::flush(std::cout);
#endif

    // Alpha 8 bit
		if (_bytesPerPixel == 1)
		{
      _internalFormat = GL_LUMINANCE;
      _pixelFormat    = GL_LUMINANCE;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
    // Luminace Alpha 16 bit
		else if (_bytesPerPixel == 2)
		{
      _internalFormat = GL_LUMINANCE_ALPHA;
      _pixelFormat    = GL_LUMINANCE_ALPHA;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
    // RGB 24 bit
		else if (_bytesPerPixel == 3)
		{
      _internalFormat = GL_RGB;
      _pixelFormat    = GL_BGR;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
		// RGBA 32 bit
		else if (_bytesPerPixel == 4)
		{
      _internalFormat = GL_RGBA;
      _pixelFormat    = GL_BGRA;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
	}
	else
	{


    // fallback
    _bytesPerPixel = 3;
    _width         = 512;
    _height        = 512;

    gloost::Image fallbackImage(_width,
                                _height,
                                _bytesPerPixel*8,
                                3,
                                0);

    fallbackImage.fill(1.0, 0.0,0.0,1.0);

    _pixelData = new BinaryBundle(fallbackImage.getPixelData(), _width*_height*_bytesPerPixel);

    _pixelData->takeReference();

    _internalFormat = GL_RGB;
    _pixelFormat    = GL_BGR;
    _pixelType      = GL_UNSIGNED_BYTE;


#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cerr << std::endl;
    std::cerr << std::endl << "ERROR in Texture::Texture() on SharedResource " << getSharedResourceId() << ":";
		std::cerr << std::endl << "         Unable to retrieve pixel data from file \"" << fileName <<  "\"";
//		std::cerr << std::endl << "         creating empty surface here, so";
//		std::cerr << std::endl << "         the program dosn't crash...";
    std::cerr << std::endl;
#endif

	}
}

///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Texture::Texture(const Image& image):
    MultiGlContext(1),
    _width(1),
    _height(1),
    _depth(1),
    _target(GL_TEXTURE_2D),
    _internalFormat(GL_RGB),
    _pixelFormat(GL_RGB),
    _pixelType(GL_UNSIGNED_BYTE),
    _dirty(GLOOST_BITMASK_ALL_SET),
    _textureUnitIdsForContexts(GLOOST_SYSTEM_NUM_RENDER_CONTEXTS, GL_TEXTURE0),
    _mipmapsEnabled(false),
    _pixelData(0),
    _bytesPerPixel(0),
    _glTexParameters(),
    _texMatrix(),
    _useTextureMatrix(0),
    _shared(0),
    _fileName()
{

	// Set some default texParameter so you will see something
  setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  setTexParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);


	// If the image loaded
	if( image.hasPixels() )
	{

		_width  = image.getWidth();
		_height = image.getHeight();
		_target = GL_TEXTURE_2D;

    _bytesPerPixel = (int)image.getBitsPerPixel()/8;

    _pixelData = new BinaryBundle(image.getPixelData(), _width*_height*_bytesPerPixel);
    _pixelData->takeReference();
    _pixelData->put(image.getPixelData(), _width*_height*_bytesPerPixel);

    // Alpha 8 bit
		if (_bytesPerPixel == 1)
		{
      _internalFormat = GL_LUMINANCE;
      _pixelFormat    = GL_LUMINANCE;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
    // Luminace Alpha 16 bit
		else if (_bytesPerPixel == 2)
		{
      _internalFormat = GL_LUMINANCE_ALPHA;
      _pixelFormat    = GL_LUMINANCE_ALPHA;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
    // RGB 24 bit
		else if (_bytesPerPixel == 3)
		{
      _internalFormat = GL_RGB;
      _pixelFormat    = GL_BGR;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
		// RGBA 32 bit
		else if (_bytesPerPixel == 4)
		{
      _internalFormat = GL_RGBA;
      _pixelFormat    = GL_BGRA;
      _pixelType      = GL_UNSIGNED_BYTE;
		}
	}
	else
	{

    // fallback
    _bytesPerPixel = 3;
    _width         = 512;
    _height        = 512;

    gloost::Image fallbackImage(_width,
                                _height,
                                _bytesPerPixel*8,
                                3,
                                0);

    fallbackImage.fill(1.0, 0.0,0.0,1.0);

    _pixelData = new BinaryBundle(fallbackImage.getPixelData(), _width*_height*_bytesPerPixel);

    _pixelData->takeReference();

    _internalFormat = GL_RGB;
    _pixelFormat    = GL_BGR;
    _pixelType      = GL_UNSIGNED_BYTE;



#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl;
    std::cout << std::endl << "ERROR in Texture::Texture() on SharedResource " << getSharedResourceId() << ":";
		std::cout << std::endl << "         Unable to retrieve pixel data from image \"" << this <<  "\"";
//		std::cout << std::endl << "         creating empty surface here, so";
//		std::cout << std::endl << "         the program dosn't crash...";
		std::flush(std::cout);
#endif

	}
}


///////////////////////////////////////////////////////////////////////////////


  /// class constructor

Texture::Texture( unsigned width,
                  unsigned height,
                  unsigned bytesPerPixel,
                  GLenum   target,
                  GLint    internalFormat,
                  GLenum   pixelFormat,
                  GLenum   pixelType):
    MultiGlContext(1),
    _width(width),
    _height(height),
    _depth(1),
    _target(target),
    _internalFormat(internalFormat),
    _pixelFormat(pixelFormat),
    _pixelType(pixelType),
    _dirty(true),
    _textureUnitIdsForContexts(GLOOST_SYSTEM_NUM_RENDER_CONTEXTS, GL_TEXTURE0),
    _mipmapsEnabled(false),
    _pixelData(new BinaryBundle(width*height*bytesPerPixel)),
    _bytesPerPixel(bytesPerPixel),
    _glTexParameters(),
    _texMatrix(),
    _useTextureMatrix(0),
    _shared(0),
    _fileName("default_texture_name.fake")
{

  _pixelData->takeReference();

  // Set some default texParameter so you will see something
  setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  setTexParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

///////////////////////////////////////////////////////////////////////////////


Texture::Texture(unsigned width,
                 unsigned height,
                 unsigned depth,
                 unsigned char* pixeldata,
                 unsigned bytesPerPixel,
                 GLenum target,
                 GLint  internalFormat,
                 GLenum pixelFormat,
                 GLenum pixelType):
    MultiGlContext(1),
    _width(width),
    _height(height),
    _depth(depth),
    _target(target),
    _internalFormat(internalFormat),
    _pixelFormat(pixelFormat),
    _pixelType(pixelType),
    _dirty(true),
    _textureUnitIdsForContexts(GLOOST_SYSTEM_NUM_RENDER_CONTEXTS, GL_TEXTURE0),
    _mipmapsEnabled(false),
    _pixelData(0),
    _bytesPerPixel(bytesPerPixel),
    _glTexParameters(),
    _texMatrix(),
    _useTextureMatrix(0),
    _shared(0),
    _fileName("default_texture_name.fake")

{

  if (pixeldata)
  {
    _pixelData = new BinaryBundle(pixeldata, width*height*depth*bytesPerPixel);
  }
  else
  {
    _pixelData = new BinaryBundle(width*height*depth*bytesPerPixel);
  }

  _pixelData->takeReference();

	// Set some default texParameter so you will see something
  setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  setTexParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  setTexParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
  setTexParameter(GL_TEXTURE_WRAP_R, GL_REPEAT);
}


///////////////////////////////////////////////////////////////////////////////


  /// destructor

Texture::~Texture()
{
  for (unsigned int i=0; i!=GLOOST_SYSTEM_NUM_RENDER_CONTEXTS; ++i)
  {
    removeFromContext(i);
  }

  freeHostData();
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// ...

void
Texture::freeHostData()
{
  /// remove the pixeldata from ram
  if (_pixelData)
  {
    _pixelData->dropReference();
    return;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// set a glTexParameter for this texture to be applied when texture is gernerated

void
Texture::setTexParameter(GLenum propertyName, float value)
{
  _glTexParameters[propertyName] = value;
  setDirty();
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// get TexParameter

float
Texture::getTexParameter(GLenum propertyName)
{
  std::map<GLenum, float>::iterator pos = _glTexParameters.find(propertyName);

  if (pos == _glTexParameters.end())
  {
    float value = 0;
    glGetTexParameterfv(_target, propertyName, &value );

    return value;
  }
  else
  {
    return (*pos).second;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// remove a TexParameter from this texture to use GL default value

void
Texture::removeTexParameter(GLenum propertyName)
{
  std::map<GLenum, float>::iterator pos = _glTexParameters.find(propertyName);

  if (pos == _glTexParameters.end())
  {
    return;
  }
  else
  {
    _glTexParameters.erase(pos);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// get a map with all Texparameter for this texture

std::map<GLenum, float>&
Texture::getTexParameterMap()
{
  return _glTexParameters;
}


///////////////////////////////////////////////////////////////////////////////


  /// get width of the texture

unsigned int
Texture::getWidth() const
{
  return _width;
}


///////////////////////////////////////////////////////////////////////////////


  /// get height of the texture

unsigned int
Texture::getHeight() const
{
  return _height;
}


///////////////////////////////////////////////////////////////////////////////


  /// get height of the texture

float
Texture::getAspecRatio() const
{
  if (_height > 0)
  {
    return (float)_width/(float)_height;
  }

  return 0.0f;
}


///////////////////////////////////////////////////////////////////////////////


  /// get gl's texture target for this texture

GLenum
Texture::getTarget()
{
  return _target;
}


///////////////////////////////////////////////////////////////////////////////


  /// get gl's internal format for this texture

GLint
Texture::getInternalFormat()
{
  return _internalFormat;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   set internal format
  \param   internalFormat Can be GL_RGB, GL_RGBA, GL_RGBA32F, GL_ALPHA, GL_DEPTH_COMPONENT32, ...
  \remarks If the Texture is allready on the GPU (after calling bind(), getTextureHandle() or initInContext) you have to call
           removeFromContext() first, to make a valid change to the Textures GPU state
*/

void
Texture::setInternalFormat(GLint internalFormat)
{
  _internalFormat = internalFormat;
}


///////////////////////////////////////////////////////////////////////////////


  /// get gl's pixel format for this texture

GLenum
Texture::getPixelFormat()
{
  return _pixelFormat;
}


///////////////////////////////////////////////////////////////////////////////


  /// get gl's pixel type for this texture

GLenum
Texture::getPixelType()
{
  return _pixelType;
}


///////////////////////////////////////////////////////////////////////////////


  /// get the GL texture handle

unsigned int
Texture::getTextureHandle(unsigned int contextId)
{

  if (!handleInContextExists(contextId))
  {
    initInContext(contextId);
  }

  return getResourceHandleForContext(contextId);
}


///////////////////////////////////////////////////////////////////////////////


  /// writes the surfaces to a jpeg file (may be upside down)

//void
//Texture::writeToFile(std::string path)
//{
////  Screenshot writer(_surface->w, _surface->h, 100);
////  writer.write(path, ( uchar* ) _surface->pixels);
//}


///////////////////////////////////////////////////////////////////////////////


  /// set the dirty flag to signal texture changes

void
Texture::setDirty()
{
  _dirty.setFlags(true);
}


///////////////////////////////////////////////////////////////////////////////


  /// unset the dirty flag to signal that texture is up to date

void
Texture::setClean(unsigned int contextId)
{
  _dirty.setFlag(contextId, false);
}


///////////////////////////////////////////////////////////////////////////////


  /// was the texture modified

bool
Texture::isDirty(unsigned int contextId) const
{
  return _dirty.getFlag(contextId);
}


///////////////////////////////////////////////////////////////////////////////


  /// generates a Gl texture from this texture

/*virtual*/
bool
Texture::initInContext(unsigned int contextId)
{

//#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
//    std::cout << std::endl;
//    std::cout << std::endl << "Message from Message from Texture::initInContext() on SharedResource " << getSharedResourceId() << ":";
//    std::cout << std::endl << "             Building for context " << contextId << ".";
//    std::cout << std::endl;
//#endif


  setResourceHandleForContext(generate(_width,
                                       _height,
                                       _depth,
                                       _target,
                                       _internalFormat,
                                       _pixelFormat,
                                       _pixelType,
                                       contextId),
                                       contextId);

  // Texture on your gpu ram is now up to date
  setClean(contextId);
  return true;
}


///////////////////////////////////////////////////////////////////////////////


  /// generates a Gl texture from this texture

unsigned int
Texture::generate( unsigned int width,
                   unsigned int height,
                   unsigned int depth,
                   GLenum target,
                   GLint internalFormat,
                   GLenum pixelFormat,
                   GLenum pixelType,
                   unsigned int contextId)
{


  unsigned int newTextureHandle = 0;


  //Create a texture
  glGenTextures(1, &newTextureHandle);

  // activate texture unit (could be redundant)
  // from otaco: it is
  // from otaco: its even deadly for UniformSets
  glActiveTexture(_textureUnitIdsForContexts[contextId]);

  // Load the texture
  glBindTexture(target, newTextureHandle);


  if (_pixelData->getSize() && target == GL_TEXTURE_2D)
  {
    // Generate the texture from Image
    if(_mipmapsEnabled)
    {

      gluBuild2DMipmaps(target,
			                  internalFormat,
			                  _width,
			                  _height,
			                  pixelFormat,
			                  pixelType,
			                  _pixelData->data());

    }
    else
    {
      glTexImage2D(target,
		   0,
		   internalFormat,
		   _width,
		   _height,
		   0,
		   pixelFormat,
		   pixelType,
		   _pixelData->data());
    }
  }
  else
  {
    if(target == GL_TEXTURE_1D)
    {
      // Generate a 1D texture
      glTexImage1D(GL_TEXTURE_1D,
                   0,
                   internalFormat,
                   width,
                   0,
                   pixelFormat,
                   pixelType,
                   _pixelData->data());
    }
    else if (target == GL_TEXTURE_2D)
    {
      // Generate a 2D texture
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   internalFormat,
                   width,
                   height,
                   0,
                   pixelFormat,
                   pixelType,
                   _pixelData->data());

    }
    else if (target == GL_TEXTURE_3D)
    {
      // Generate a 2D texture
      glTexImage3D(GL_TEXTURE_3D,
                   0,
                   internalFormat,
                   width,
                   height,
                   depth,
                   0,
                   pixelFormat,
                   pixelType,
                   _pixelData->data());
    }

  }

  // add texParameter
  std::map<GLenum, float>::const_iterator index = _glTexParameters.begin();
  std::map<GLenum, float>::const_iterator ende  = _glTexParameters.end();

  for (; index != ende; index++ )
  {
    glTexParameterf(_target, (*index).first, (*index).second);
  }

  glBindTexture(target, 0);

  return newTextureHandle;
}


///////////////////////////////////////////////////////////////////////////////


  /// remove a resource from a context

/*virtual*/
void
Texture::removeFromContext(unsigned int contextId)
{
  if (handleInContextExists(contextId))
  {
    glDeleteTextures(1, &getResourceHandleForContext(contextId) );
    setResourceHandleForContext(0, contextId);
  }
  setDirty();
}


///////////////////////////////////////////////////////////////////////////////


  /// binds the Texture to GL state

void
Texture::bind(unsigned int texUnitId, unsigned int contextId)
{
  /// set internal id needed for unbind
  _textureUnitIdsForContexts[contextId] = texUnitId;


  /// if this texture is not up to date we have to remove it first from the gpu ram
  if (_dirty.getFlag(contextId))
  {

    if (handleInContextExists(contextId))
    {
      removeFromContext(contextId);
    }

    /// generate and setClean
    initInContext(contextId);
  }


  /// is this case possible???
  if (!handleInContextExists(contextId))
  {
    initInContext(contextId);
  }


  // activate texture unit (could be redundant)
  glActiveTexture(texUnitId);


  // bind the texture to the unit
  glBindTexture(_target, getResourceHandleForContext(contextId));


  // apply texture matrix if needed
  if (_useTextureMatrix)
  {
    glMatrixMode(GL_TEXTURE);
    gloostLoadMatrix(_texMatrix.data());
    glMatrixMode(GL_MODELVIEW);
  }

}


///////////////////////////////////////////////////////////////////////////////


  /// unbind Texture

void
Texture::unbind(unsigned int contextId)
{
	/// yes we do! just for safety
	glActiveTexture(_textureUnitIdsForContexts[contextId]);

	// bind zero to this unit to disable this texture
	glBindTexture(_target, 0);

  // apply texture matrix if needed
  if (_useTextureMatrix)
  {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
  }
}


///////////////////////////////////////////////////////////////////////////////


  /// read the (changed) texture from the gfx-card back into the surface

void
Texture::readBack()
{

  /* http://www.mathematik.uni-dortmund.de/~goeddeke/gpgpu/tutorial.html
     glGetTexImage: http://developer.3dlabs.com/documents/glmanpages/glgetteximage.htm
  */

  bind();

  if (!_pixelData)
  {
    std::cout << std::endl << "-> : " << " allocating pixel buffer";
    _pixelData = new BinaryBundle(_width*_height*_bytesPerPixel);
    _pixelData->takeReference();
  }

  std::cout << std::endl << "-> : " << " done";

  glGetTexImage(_target,
                0,
                _internalFormat,
                _pixelType,
                _pixelData->data());
  unbind();
}


///////////////////////////////////////////////////////////////////////////////


/// set the texture matrix
void
Texture::setTextureMatrix(const Matrix& matrix)
{
  _texMatrix = matrix;
}


///////////////////////////////////////////////////////////////////////////////


  /// get the texture matrix

const Matrix&
Texture::getTextureMatrix()
{
  return _texMatrix;
}


///////////////////////////////////////////////////////////////////////////////


  /// use the textureMatrix

void
Texture::enableTextureMatrix(bool trueOrFalse)
{
  _useTextureMatrix = trueOrFalse;
}


///////////////////////////////////////////////////////////////////////////////


  /// returns true if texture matrix is enabled

bool
Texture::isTextureMatrixEnabled()
{
  return _useTextureMatrix;
}


///////////////////////////////////////////////////////////////////////////////


  /// use Mipmapping (don't work if attachet to an Fbo)

void
Texture::enableMipmaps(bool trueOrFalse)
{
   _mipmapsEnabled = trueOrFalse;

  if(_mipmapsEnabled)
  {
    setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
  else
  {
    setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  setDirty();
}


///////////////////////////////////////////////////////////////////////////////


  /// returns 1 if Mipmapping is enabled

bool
Texture::isMipmapsEnabled()
{
   return _mipmapsEnabled;
}


///////////////////////////////////////////////////////////////////////////////



/// set this texture shared or unshared (this flag is used by the TextureManager)
void
Texture::setShared(bool shared)
{
   _shared = shared;
}

///////////////////////////////////////////////////////////////////////////////



/// returns 1 if this texture is shared within the TextureManager
bool
Texture::isShared()
{
   return _shared;
}


///////////////////////////////////////////////////////////////////////////////


  /// returns a pointer to the pixel data

unsigned char*
Texture::getPixels()
{
   return _pixelData->data();
}


///////////////////////////////////////////////////////////////////////////////


  /// returns a pointer to the pixel data within a BinaryBundle

BinaryBundle*
Texture::getPixelBundle()
{
   return _pixelData;
}

///////////////////////////////////////////////////////////////////////////////


  /// replaces pixeldata on host side, new pixels must have same format as old ones! (Texture will not become _dirty)

void
Texture::updatePixels(unsigned char* pixelbuffer,
                      unsigned int   lengthInByte)
{
  // update host side
  _pixelData->rewind();
  _pixelData->put(pixelbuffer, lengthInByte);
}

///////////////////////////////////////////////////////////////////////////////



  /// get the filename of this texture

std::string
Texture::getFileName() const
{
   return _fileName;
}


////////////////////////////////////////////////////////////////////////////////


/* extern */
std::ostream&
operator<< (std::ostream& os, const Texture& texture)
{

  os << std::endl << "Texture" << std::endl << "{";
  os << std::endl << "    SharedResourceId: " << texture.getWidth();
  os << std::endl << "    width:            " << texture.getWidth();
  os << std::endl << "    height:           " << texture.getHeight();
  os << std::endl;
  os << std::endl << "    referenced:       " << texture.isReferenced();
  os << std::endl << "    refcount:         " << texture.getReferenceCount();
  os << std::endl;

  os << std::endl << "} // Texture" << std::endl;
  std::flush(os);

  return os;
}



} // namespace gloost
