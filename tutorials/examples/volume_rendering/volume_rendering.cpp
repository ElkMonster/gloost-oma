
// for glut win32
#define _STDCALL_SUPPORTED
#define _M_IX86

/// cpp includes
#ifdef LINUX
  #include <SDL/SDL.h>
#else
  #include <SDL.h>
#endif


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <list>


/// gloost includes
#include <SDL_Screen.h>
#include <EventHandler.h>
#include <TextureManager.h>
#include <Texture.h>
#include <Particle.h>
#include <ParticleHandler.h>
#include <gloostRenderGoodies.h>
#include <gloostHelper.h>
#include <gloostMath.h>
#include <TextureText.h>
#include <Shader.h>
#include <UniformSet.h>
#include <Dcs.h>


///////////////////////////////////////////////////////////////////////////////


// Screen attributes
const int g_screenWidth  = 1280;
const int g_screenHeight = 720;
const int g_screen_bpp   = 32;


// The screen
gloost::SDL_Screen g_screen(g_screenWidth, g_screenHeight, g_screen_bpp);


// EventHandler to handle game input
gloost::EventHandler g_input(&g_screen);

// frame counter
unsigned int g_frameCounter = 0;

/// geometry and texture stuff
gloost::TextureManager*  g_texManager      = 0;
unsigned int             g_gloostTextureId = 0;

unsigned int             g_volumeTextureId = 0;

/// text from a texture
gloost::TextureText* g_textMaker = 0;


// shader
gloost::Shader*     g_volumeShader   = 0;
gloost::UniformSet* g_volumeUniforms = 0;


unsigned int   g_volumeSize = 256;

float g_min_density  = 0.3f;
float g_max_density  = 0.54f;
float g_density_step = 0.01f;


float g_objRotateX = 0.0f;
float g_objRotateY = -45.0f;

float g_cameraZoom = 2.8f;

float g_resolutionMove = 2.0f;
float g_resolutionMax  = 0.25f;
float g_resolution     = g_resolutionMax;
float g_resolutionStep = 0.1f;


bool g_frameDone = false;



///////////////////////////////////////////////////////////////////////////////


void clean_up()
{
  //Quit SDL
  SDL_Quit();
}


///////////////////////////////////////////////////////////////////////////////


  ///

void render2d()
{

  glPushMatrix();
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    {

      glViewport(0, 0, g_screenWidth, g_screenHeight);



      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, (float) g_screenWidth, 0, (float) g_screenHeight, 0.1, 10.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0.0, 0.0, 5.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);

      // color
      glColor3d(1,1,1);

      // gloost logo

      glDisable(GL_CULL_FACE);

      gloost::Texture* logoTexture = g_texManager->getTextureWithoutRefcount(g_gloostTextureId);

      logoTexture->bind();
      {
        glPushMatrix();
          glTranslatef(10.0, logoTexture->getHeight()/2.0, 0.0);
          glScalef(logoTexture->getWidth()/2.0,
                   -(float)logoTexture->getHeight()/2.0,
                   1.0f);
          gloost::drawQuad();
        glPopMatrix();
      }
      logoTexture->unbind();

    }
    glPopAttrib();
  }
  glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////


inline void drawQuadCenter()
{
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f  (-0.5f, 0.5f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f  (-0.5f, -0.5f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f  (0.5f, -0.5f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f  (0.5f,  0.5f, 0.0f);
  }
  glEnd();
}


///////////////////////////////////////////////////////////////////////////////


  ///

inline void renderVolume(void)
{

   ++g_frameCounter;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (25.0f,
                 (GLfloat)(g_screenWidth)/(GLfloat)(g_screenHeight),
                 0.1f, 50.0f),

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(-0.128, 0.0, g_cameraZoom,
            -0.128, 0.0, 0.5,
            0.0f, 1.0f, 0.0f);


  //
  glPushAttrib(GL_ALL_ATTRIB_BITS);
 {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);


    g_volumeShader->set();

    g_volumeUniforms->set_float("min_d",       g_min_density);
    g_volumeUniforms->set_float("max_d",       g_max_density);
    g_volumeUniforms->set_float("invDelta_d", 1.0/(g_max_density-g_min_density));
    g_volumeUniforms->set_float("alphaMult",  g_resolution);



    gloost::Matrix volumeTexStaticCorrectionSpecialMatrix;
    volumeTexStaticCorrectionSpecialMatrix.setIdentity();
    volumeTexStaticCorrectionSpecialMatrix.setRotate(gloost::deg2rad(90.0), 0.0, 0.0);

    gloost::Matrix volumeTexRot;
    volumeTexRot.setIdentity();
    volumeTexRot.setRotate(gloost::deg2rad(g_objRotateX), gloost::deg2rad(g_objRotateY), 0.0);

    gloost::Matrix volumeTexTrans;
    volumeTexTrans.setIdentity();
    volumeTexTrans.setTranslate(-0.5,-0.5,-0.5);


    gloost::Matrix volumeTexTransform = volumeTexStaticCorrectionSpecialMatrix*volumeTexRot*volumeTexTrans;

    volumeTexTrans.setIdentity();
    volumeTexTrans.setTranslate(0.5,0.5,0.5);

    volumeTexTransform = volumeTexTrans*volumeTexTransform;
    g_texManager->getTextureWithoutRefcount(g_volumeTextureId)->setTextureMatrix(volumeTexTransform);


    glPushMatrix();
    {

      //glRotatef(gloost::rad2deg(g_frameCounter*0.01), 0.0, 1.0, 0.0);

      float quadStepWidth = 1.0/g_volumeSize;

      for (int i=0; i<g_volumeSize/g_resolution; ++i )
      {

        glPushMatrix();
        {
          glTranslatef(0.0, 0.0, quadStepWidth*i*g_resolution);
          g_volumeUniforms->set_float("depth_w",  (i*quadStepWidth)*g_resolution);
          g_volumeUniforms->applyToShader(g_volumeShader->getShaderHandle());

          drawQuadCenter();

        }
        glPopMatrix();
      }

    }
    glPopMatrix();

    g_volumeShader->disable();


  }
  glPopAttrib();



  // Text
  g_textMaker->begin();

    g_textMaker->renderTextLine(10.0, g_screenHeight-25.0, std::string("gloost volume_rendering: ")+gloost::toString(g_frameCounter));

    g_textMaker->renderFreeLine();

    g_textMaker->renderTextLine(std::string("(a,q) ... min density: ... ")+gloost::toString(g_min_density));
    g_textMaker->renderTextLine(std::string("(s,w) ... max density: ... ")+gloost::toString(g_max_density));
    g_textMaker->renderTextLine(std::string("(f,r) ... move band:  .... ")+gloost::toString((g_max_density+g_min_density)/2.0));
    g_textMaker->renderTextLine(std::string("      --> bandwidth: ..... ")+gloost::toString(g_max_density-g_min_density));

    g_textMaker->renderFreeLine();

    g_textMaker->renderTextLine(std::string("Use the right mouse button to rotate the volume: "));
    g_textMaker->renderTextLine(std::string("rotate x: ")+gloost::toString(g_objRotateX));
    g_textMaker->renderTextLine(std::string("rotate y: ")+gloost::toString(g_objRotateY));

    g_textMaker->renderFreeLine();

    g_textMaker->renderTextLine(std::string("Use the right mouse button to zoom: "));
    g_textMaker->renderTextLine(std::string("zoom: ")+gloost::toString(g_cameraZoom));

    g_textMaker->renderFreeLine();

    g_textMaker->renderTextLine(std::string("(g,t) ... resolution: ")+gloost::toString(g_resolution)+std::string("/") +gloost::toString(g_resolutionMove));


  g_textMaker->end();



  if (g_resolution == g_resolutionMax)
  {
    g_frameDone = true;
  }

}


///////////////////////////////////////////////////////////////////////////////


  /// loads the resources

void init ()
{
  // Textures
  g_texManager          = gloost::TextureManager::getInstance();
  g_gloostTextureId     = g_texManager->createTexture("../../data/images/gloost_bar_logo.png");


  // init TextureText object with a texture
  g_textMaker = new gloost::TextureText("../../data/fonts/gloost_Fixedsys_16_gui.png");
  g_textMaker->setCharSpace(-9);

  g_volumeShader = new gloost::Shader("../../shaders/volume_shader_0.01.vs",
                                      "../../shaders/volume_shader_0.01.fs");

  g_volumeUniforms = new gloost::UniformSet();



  // create volume data
  const unsigned int volsize = g_volumeSize*g_volumeSize*g_volumeSize;
  unsigned char* volumeData = new unsigned char [volsize] ;


  if (1)
  {
    // load a raw file
    FILE* volfile = fopen("../../data/volumes/head_w256_h256_d225_c1_b8.raw","rb");

    if(!volfile)
    {
      std::cout << "error opening volume file" << std::endl;
    }
    else
    {
      std::cerr << std::endl << "Loading volume...";
    }

    fseek (volfile , 0 , SEEK_END);
    long volFileSize = ftell (volfile);
    rewind (volfile);
    fread (volumeData,1,volFileSize,volfile);
    fclose(volfile);
  }


  // Volume

  gloost::Texture* volumeTexture = new gloost::Texture(g_volumeSize,
                                                       g_volumeSize,
                                                       225,
                                                       volumeData,
                                                       GL_TEXTURE_3D,
                                                       GL_ALPHA,
                                                       GL_ALPHA,
                                                       GL_UNSIGNED_BYTE);
  volumeTexture->setTexParameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
  volumeTexture->setTexParameter(GL_TEXTURE_WRAP_T, GL_CLAMP);
  volumeTexture->setTexParameter(GL_TEXTURE_WRAP_R, GL_CLAMP);
  volumeTexture->enableTextureMatrix();

  g_volumeTextureId = g_texManager->addTexture(volumeTexture);
  g_volumeUniforms->set_sampler3D("map_volumen", g_volumeTextureId);


  // Transfer texture
  gloost::Texture* transferTexture = new gloost::Texture("../../data/gradiens/rainbow.jpg");
  unsigned int transferTexId = g_texManager->addTexture(transferTexture);
  g_volumeUniforms->set_sampler2D("map_transfer", transferTexId);
//  transferTexture->enableTextureMatrix();

}


///////////////////////////////////////////////////////////////////////////////

inline void checkEvents ()
{

  g_resolution = g_resolutionMax;

  float bandWith =g_max_density-g_min_density;

  // min clamp
  if(g_input.getKeyState(SDLK_q) && bandWith > 0.05)
  {
    g_min_density += g_density_step;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }
  if(g_input.getKeyState(SDLK_a) && g_min_density > g_density_step)
  {
    g_min_density -= g_density_step;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }


  // max clamp
  if(g_input.getKeyState(SDLK_w) && g_max_density < 1.0)
  {
    g_max_density += g_density_step;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }
  if(g_input.getKeyState(SDLK_s) && bandWith > 0.05)
  {
    g_max_density -= g_density_step;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }


  // move band
  if(g_input.getKeyState(SDLK_r) && g_max_density < 1.0)
  {
    g_min_density += g_density_step;
    g_max_density += g_density_step;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }
  if(g_input.getKeyState(SDLK_f) && g_min_density > g_density_step)
   {
    g_min_density -= g_density_step;

    g_max_density -= g_density_step;
    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }


  // resolution
  if(g_input.getKeyState(SDLK_t) && g_resolutionMove < 10.0-g_resolutionStep)
  {
    g_resolutionMove += g_resolutionStep;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }
  if(g_input.getKeyState(SDLK_g) && g_resolutionMove > 0.25+g_resolutionStep)
  {
    g_resolutionMove -= g_resolutionStep;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }


  // rotate object
  if (g_input.getMouse()->getButtonState(GLOOST_MOUSE_BUTTON1))
  {
    g_objRotateX -= g_input.getMouse()->getSpeed()[1]*0.3;
    g_objRotateY -= g_input.getMouse()->getSpeed()[0]*0.3;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }

  // zoom object
  if (g_input.getMouse()->getButtonState(GLOOST_MOUSE_BUTTON2))
  {
    g_cameraZoom += g_input.getMouse()->getSpeed()[1]*0.01;

    g_resolution = g_resolutionMove;
    g_frameDone = false;
  }
}



///////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{

  #ifdef __APPLE__ || __MACH__ || OSX
    glutInit(&argc,argv);
  #endif

  #ifdef LINUX
    setenv("__GL_SYNC_TO_VBLANK","1",true);
  #else
    // SDL console output hack
    freopen( "CON", "w", stdout );
  #endif


  /// configure the screen
  g_screen.setCaptionText("SDL EXAMPLE");
  g_screen.addFlags(SDL_SRCALPHA | SDL_ANYFORMAT | SDL_OPENGL);
//  g_screen.addFlags(SDL_FULLSCREEN);


  //Initialize
  if( g_screen.init() == false )
  {
      return 1;
  }


  // Init glew
  if (GLEW_OK != glewInit())
  {
    std::cout << "'glewInit()' failed." << std::endl;
    exit(0);
  }


  // some gl state calls
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);



  /// loading ...
  init();



  // main loop
  while (!g_input.getKeyState(SDLK_ESCAPE))
  {



      /// update event handler
      g_input.update();

      /// handle events
      checkEvents();


      if (g_frameDone == false)
      {
        /// render 3d content
        renderVolume();

        /// render 2d content
        render2d();


        glFlush();
        SDL_GL_SwapBuffers();
      }
  }


  // clean up sdl
  clean_up();



  return 0;
}
