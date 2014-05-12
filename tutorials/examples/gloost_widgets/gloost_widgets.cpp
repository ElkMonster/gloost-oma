
/*
  author: 2008 by Felix Weizig
  mail:   thesleeper@gmx.net

*/

// for glut
#define _STDCALL_SUPPORTED
#define _M_IX86



/// gloost includes
#include<Shader.h>
#include<Texture.h>
#include<Shader.h>
#include<UniformSet.h>
#include<Fbo.h>
#include<TextureManager.h>
#include<gloostRenderGoodies.h>
#include<gloostHelper.h>
#include<gloostMath.h>
#include<TextureText.h>
#include<TextLog.h>
#include<Mouse.h>
#include<gui/Gui.h>


/// cpp / std includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <map>


//////////////////////////////////////////////////////////////////////////////////////////


unsigned int g_screenWidth  = 1024;
unsigned int g_screenHeight = 640;

// textureManager
gloost::TextureManager* g_texMaster = 0;

// texture text
gloost::TextureText* g_texter = 0;


gloost::Mouse* g_mouse = new gloost::Mouse();

// object control
float g_objectZoom        = 3.5;
float g_objectZoomSpeed   = 0.1;



// benchmark
unsigned int g_lastFrameTime = 0;


unsigned int g_frameCounter = 0;



// gui
gloost::Gui* g_gui = 0;




//////////////////////////////////////////////////////////////////////////////////////////


static void resize(int width, int height)
{
    g_screenWidth  = width;
    g_screenHeight = height;

    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 3.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// perspective setup for content rendering

inline void switchToScenePerspective()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (25.0f, (GLfloat)(g_screenWidth)/(GLfloat)(g_screenHeight),	0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0.0, 0.0,  g_objectZoom,
            0.0, 0.0,  0.0,
            0.0, 1.0,  0.0);
}


//////////////////////////////////////////////////////////////////////////////////////////


  /// applies object transformations for mesh and uv_mesh

inline void applyContentTransformations()
{
  glTranslatef(-0.2, 0.05, 0.0);
}


//////////////////////////////////////////////////////////////////////////////////////////


static void display(void)
{

  ++g_frameCounter;



  if (g_frameCounter % 3 == 0)
  {
    gloost::Histogram* mouseSpeedHisto = static_cast<gloost::Histogram*>(g_gui->getWidgetByName("mouseSpeedHisto"));
    float mouseSpeed = g_gui->getMouse()->getSpeed().distanceToOrigin();
    mouseSpeedHisto->addToGraph(mouseSpeed);
  }


  if (g_gui->frameStep())
  {

  }


  // clear the framebuffer
  glClearColor(0.215, 0.215, 0.215, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();



  g_gui->draw();


//  g_textLog->draw();


  glutSwapBuffers();


}


//////////////////////////////////////////////////////////////////////////////////////////


void motionFunc(int mouse_h, int mouse_v)
{
  // set the mouse
  g_gui->glutMotionFunc(mouse_h, g_screenHeight - mouse_v);
}


//////////////////////////////////////////////////////////////////////////////////////////


void mouseFunc(int button, int state, int mouse_h, int mouse_v)
{
   g_gui->glutMouseFunc(button, state, mouse_h, g_screenHeight - mouse_v);
}


//////////////////////////////////////////////////////////////////////////////////////////


//void MouseWheel(int wheel, int direction, int x, int y)
//{
//	if (direction > 0)
//	{
//		g_textLog->scrollUp(3);
//	}
//	else
//	{
//    g_textLog->scrollDown(3);
//	}
//}


//////////////////////////////////////////////////////////////////////////////////////////


static void key(unsigned char key, int x, int y)
{

  if (!g_gui->handleKeyDownEvent(key))
  switch (key)
  {

    // quit
    case 27 :
        //g_textLog->writeLog(std::string("gui_test_TextLog") + ".log");
        exit(0);
        break;

    // fullscreen
    case 'f' :
        glutFullScreen();
        break;

    /// clear log
    case 'd' :
        g_gui->toggleDragMode();
        gloost::TextLog::getInstance()->addLine();
        gloost::TextLog::getInstance()->addLine("   ---> toggle dragmode for all Widgets",
                                                 gloost::vec3(0.85, 0.7, 0.2));
        gloost::TextLog::getInstance()->addLine();
        break;

    case 'i':
      g_gui->getWidgetByName("group_text")->writeXml("group_text.xml");
      break;
    case 'o':
      g_gui->getWidgetByName("group_text")->readXml("group_text.xml");
      break;


  }

}


//////////////////////////////////////////////////////////////////////////////////////////


static void idle(void)
{
    glutPostRedisplay();
}


//////////////////////////////////////////////////////////////////////////////////////////


void init()
{
  // text output
  g_texter = new gloost::TextureText("../../data/fonts/gloost_BitstreamVeraSansMono_16.png");


  /// get the gui
  g_gui = new gloost::Gui;


  /// slider
  gloost::Slider* slider0 = new gloost::Slider("slider_0",
                                               "Slider {0 ... 100}, float",
                                               gloost::Vector2(400.0f, 420.0f),
                                               gloost::Vector2(200.0f, 24.0f),
                                               0.0f,
                                               100.0f,
                                               50.0f);
  g_gui->addWidget(slider0);




  gloost::Slider* slider1 = new gloost::Slider("slider_1",
                                               "Slider {0 ... 25}, int",
                                               gloost::Vector2(400.0f, 360.0f),
                                               gloost::Vector2(200.0f, 24.0f),
                                               0.0f,
                                               25.0f,
                                               1.0f,
                                               "int");

  g_gui->addWidget(slider1);




  gloost::Slider* slider2 = new gloost::Slider("slider_2",
                                               "Slider {-100 ... 100}, int",
                                               gloost::Vector2(400.0f, 300.0f),
                                               gloost::Vector2(200.0f, 24.0f),
                                               -100.0f,
                                               100.0f,
                                               0.0f,
                                               "int");
  g_gui->addWidget(slider2);




  gloost::Slider* slider3 = new gloost::Slider("slider_3",
                                               "Slider {0.0 ... 1.0}, float",
                                               gloost::Vector2(400.0f, 240.0f),
                                               gloost::Vector2(200.0f, 20.0f));
  g_gui->addWidget(slider3);





  /// toggles
  gloost::Toggle* toggle0 = new gloost::Toggle("toggle_enable_gloost",
                                               "enable gloost boost",
                                               gloost::Vector2(400.0f, 500.0f),
                                               gloost::Vector2(14.0f, 14.0f));
  g_gui->addWidget(toggle0);


  gloost::Toggle* toggle1 = new gloost::Toggle("toggle_enable_shader",
                                               "enable shader",
                                               gloost::Vector2(400.0f, 530.0f),
                                               gloost::Vector2(14.0f, 14.0f));

  g_gui->addWidget(toggle1);


  gloost::Button* Button0 = new gloost::Button("button_start",
                                               "a simple button",
                                               gloost::Vector2(400.0f, 580.0f),
                                               gloost::Vector2(12.0f, 10.0f));



  g_gui->addWidget(Button0);


  gloost::Pad* Pad0 = new gloost::Pad("pad_01",
                                      "XY-Pad, configured as int",
                                       gloost::Vector2(400.0f, 20.0f),
                                       gloost::Vector2(180.0f, 180.0f),
                                       -100.0f, 100.0f, 0.0f,
                                       -100.0f, 100.0f, 0.0f,
                                       "int");
  g_gui->addWidget(Pad0);



  gloost::TextInput* textInput1 = new gloost::TextInput("textInput1",
                                                        "text input field",
                                                        "empty 1",
                                                         gloost::Vector2(640.0f, 180.0f),
                                                         gloost::Vector2(170.0f, 20.0f));
  g_gui->addWidget(textInput1);

  gloost::TextInput* textInput2 = new gloost::TextInput("textInput2",
                                                        "text input field",
                                                        "empty 2",
                                                         gloost::Vector2(640.0f, 100.0f),
                                                         gloost::Vector2(170.0f, 20.0f));
  g_gui->addWidget(textInput2);

  gloost::TextInput* textInput3 = new gloost::TextInput("textInput3",
                                                        "text input field",
                                                        "empty 3",
                                                         gloost::Vector2(640.0f, 20.0f),
                                                         gloost::Vector2(170.0f, 20.0f));
  g_gui->addWidget(textInput3);


  gloost::PropertyInspector* propInsp = new gloost::PropertyInspector("propInsp",
                                                                      gloost::Vector2(20.0f,  20.0f),
                                                                      gloost::Vector2(350.0f, 580.0f));



  g_gui->addWidget(propInsp);


  gloost::WidgetGroup* group_text = new gloost::WidgetGroup("group_text",
                                                            "Textinputs",
                                                            gloost::Vector2(640.0f,  250.0f));

  group_text->addWidget(textInput1);
  group_text->addWidget(textInput2);
  group_text->addWidget(textInput3);

  g_gui->addWidget(group_text);



  /// Histogram

  gloost::Histogram* mouseSpeedHisto = new gloost::Histogram("mouseSpeedHisto",
                                                             "mouse speed",
                                                             gloost::Vector2(700,485),
                                                             gloost::Vector2(300.0f, 120.0f),
                                                             0.0f,
                                                             10.0f);
  mouseSpeedHisto->toggleMeanUse();
  mouseSpeedHisto->setProp("_resizeGraph", true);

  g_gui->addWidget(mouseSpeedHisto);

}


//////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(g_screenWidth,g_screenHeight);
  glutInitWindowPosition(80,20);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutCreateWindow("gloost_widgets");

  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutMotionFunc(motionFunc);
  glutPassiveMotionFunc(motionFunc);
  glutMouseFunc(mouseFunc);

	if (GLEW_OK != glewInit())
	{
	  std::cerr << "'glewInit()' failed." << std::endl;
	  exit(0);
  }


  // SDL console output
  freopen( "CON", "w", stdout );


  glClearColor(0.215, 0.215, 0.215, 1.0);

//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);



  ////////////////////////////////////////////////////////////////////////////////////////
  // Test
  ////////////////////////////////////////////////////////////////////////////////////////


  /// load stuff
  init();





  glutMainLoop();


  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////////////////



