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
#include <Fbo.h>



/// cpp includes
#include <iostream>



///////////////////////////////////////////////////////////////////////////////


namespace gloost
{

/// constructor

Fbo::Fbo():
  _fboHandle(0),
  _savedFboHandle(0)
{
  // generate Fbo handle
  _fboHandle = generate();
}


//////////////////////////////////////////////////////////////////////////////////////////


///

Fbo::~Fbo()
{
  glDeleteFramebuffersEXT(1, &_fboHandle);
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::bind(unsigned int attachment)
{
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fboHandle);
  glDrawBuffer(attachment);
}


//////////////////////////////////////////////////////////////////////////////////////////


/// returns the OpenGL handle for this FBO

unsigned int
Fbo::getFboHandle()
{
  return _fboHandle;
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::disable()
{
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::attachTexture( GLenum texTarget, GLuint textureHandle,
                    GLenum attachment, int mipLevel, int zSlice )
{
  guardedBind();

  // Check if texture is allready attached
  if ( getAttachedId(attachment) != textureHandle )
  {
    attachTextureByTargetType( attachment, texTarget, textureHandle, mipLevel, zSlice );
  }
  else
  {
    std::cerr << "Fbo::AttachTexture PERFORMANCE WARNING:\n"
              << "\tRedundant bind of texture (id = " << textureHandle << ")." << std::endl;
  }

  guardedUnbind();
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::attachTextures( int numTextures, GLenum texTarget[], GLuint texId[],
                     GLenum attachment[], int mipLevel[], int zSlice[] )
{
  for (int i = 0; i < numTextures; ++i)
  {
    attachTexture( texTarget[i], texId[i],
                   attachment ? attachment[i] : (GL_COLOR_ATTACHMENT0_EXT + i),
                   mipLevel ? mipLevel[i] : 0,
                   zSlice ? zSlice[i] : 0 );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::attachRenderBuffer( GLuint buffId, GLenum attachment )
{
  guardedBind();

#ifndef NDEBUG
  if ( getAttachedId(attachment) != buffId )
  {
#endif

    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, attachment,
                                 GL_RENDERBUFFER_EXT, buffId);

#ifndef NDEBUG
  }
  else
  {
    std::cerr << "Fbo::AttachRenderBuffer PERFORMANCE WARNING:\n"
              << "\tRedundant bind of Renderbuffer (id = " << buffId << ")\n"
              << "\tHINT : Compile with -DNDEBUG to remove this warning.\n";
  }
#endif

  guardedUnbind();
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::attachRenderBuffers( int numBuffers, GLuint buffId[], GLenum attachment[] )
{
  for (int i = 0; i < numBuffers; ++i)
  {
    attachRenderBuffer( buffId[i], attachment ? attachment[i] : (GL_COLOR_ATTACHMENT0_EXT + i) );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::unattach( GLenum attachment )
{
  guardedBind();
  GLenum type = getAttachedType(attachment);

  switch (type)
  {
  case GL_NONE:
    break;
  case GL_RENDERBUFFER_EXT:
    attachRenderBuffer( 0, attachment );
    break;
  case GL_TEXTURE:
    attachTexture( GL_TEXTURE_2D, 0, attachment );
    break;
  default:
    std::cerr << "Fbo::unbind_attachment ERROR: Unknown attached resource type\n";
  }
  guardedUnbind();
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::unattachAll()
{
  int numAttachments = getMaxColorAttachments();
  for (int i = 0; i < numAttachments; ++i)
  {
    unattach( GL_COLOR_ATTACHMENT0_EXT + i );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


///

/* static */
GLint
Fbo::getMaxColorAttachments()
{
  GLint maxAttach = 0;
  glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS_EXT, &maxAttach );
  return maxAttach;
}


//////////////////////////////////////////////////////////////////////////////////////////


/// generate FBO

GLuint
Fbo::generate()
{
  GLuint id = 0;
  glGenFramebuffersEXT(1, &id);

  return id;
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::guardedBind()
{
  // Only binds if m_fboHandle is different than the currently bound FBO
  glGetIntegerv( GL_FRAMEBUFFER_BINDING_EXT, &_savedFboHandle );
  if (_fboHandle != (GLuint)_savedFboHandle)
  {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fboHandle);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::guardedUnbind()
{
  // Returns FBO binding to the previously enabled FBO
  if (_fboHandle != (GLuint)_savedFboHandle)
  {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, (GLuint)_savedFboHandle);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


///

void
Fbo::attachTextureByTargetType( GLenum attachment,
                                GLenum texTarget,
                                GLuint texId,
                                int mipLevel,
                                int zSlice )
{

  switch (texTarget)
  {
  case GL_TEXTURE_1D:
    glFramebufferTexture1DEXT( GL_FRAMEBUFFER_EXT,
                               attachment,
                               GL_TEXTURE_1D,
                               texId,
                               mipLevel );
    break;

// 2010-03-23 thiesje: only supported with extension EXT_texture_array
#ifdef GL_EXT_texture_array
  case GL_TEXTURE_2D_ARRAY_EXT:
    glFramebufferTextureEXT( GL_FRAMEBUFFER_EXT,
                             attachment,
                             texId,
                             zSlice);
    break;
#endif /* GL_EXT_texture_array */

  case GL_TEXTURE_3D:
    glFramebufferTexture3DEXT( GL_FRAMEBUFFER_EXT,
                               attachment,
                               GL_TEXTURE_3D,
                               texId,
                               mipLevel,
                               zSlice );
    break;


  case GL_TEXTURE_RECTANGLE_ARB:
  case GL_TEXTURE_2D:
  default:
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT,
                               attachment,
                               texTarget,
                               texId,
                               mipLevel );
    break;
  }

}


//////////////////////////////////////////////////////////////////////////////////////////


///

#ifndef NDEBUG
bool
Fbo::isValid( std::ostream& ostr )
{
  guardedBind();

  bool isOK = false;

  GLenum status;
  status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  switch (status)
  {
  case GL_FRAMEBUFFER_COMPLETE_EXT: // Everything's OK
    isOK = true;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n";
    isOK = false;
    break;
  case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "GL_FRAMEBUFFER_UNSUPPORTED_EXT\n";
    isOK = false;
    break;
  default:
    ostr << "glift::CheckFramebufferStatus() ERROR:\n\t"
    << "Unknown ERROR\n";
    isOK = false;
  }

  guardedUnbind();
  return isOK;
}
#endif // NDEBUG


//////////////////////////////////////////////////////////////////////////////////////////


/// Accessors

GLenum
Fbo::getAttachedType( GLenum attachment )
{
  // Returns GL_RENDERBUFFER_EXT or GL_TEXTURE
  guardedBind();
  GLint type = 0;
  glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment,
      GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT,
      &type);
  guardedUnbind();
  return GLenum(type);
}


//////////////////////////////////////////////////////////////////////////////////////////


///

GLuint
Fbo::getAttachedId( GLenum attachment )
{
  guardedBind();
  GLint id = 0;
  glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment,
      GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT,
      &id);
  guardedUnbind();
  return GLuint(id);
}


//////////////////////////////////////////////////////////////////////////////////////////


///

GLint
Fbo::getAttachedMipLevel( GLenum attachment )
{
  guardedBind();
  GLint level = 0;
  glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment,
      GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT,
      &level);
  guardedUnbind();
  return level;
}


//////////////////////////////////////////////////////////////////////////////////////////


///

GLint
Fbo::getAttachedCubeFace( GLenum attachment )
{
  guardedBind();
  GLint level = 0;
  glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment,
      GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT,
      &level);
  guardedUnbind();
  return level;
}


//////////////////////////////////////////////////////////////////////////////////////////


///

GLint
Fbo::getAttachedZSlice( GLenum attachment )
{
  guardedBind();
  GLint slice = 0;
  glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment,
      GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT,
      &slice);
  guardedUnbind();
  return slice;
}


//////////////////////////////////////////////////////////////////////////////////////////


///



} // namespace gloost
