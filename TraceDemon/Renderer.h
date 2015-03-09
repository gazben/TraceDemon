#ifndef Renderer_h__
#define Renderer_h__

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <vector>

#include <thread>
#include <mutex>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "Scene.h"
#include "Config.h"
#include "Rectangle.h"

inline void onInitialization() {
  glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
}

inline void onKeyboard(unsigned char key, int x, int y) {
}

inline void onKeyboardUp(unsigned char key, int x, int y) {
}

inline void onMouse(int button, int state, int x, int y) {
}

inline void onMouseMotion(int x, int y){
}

inline void onIdle();
inline void onDisplay();



//This class contains the current rendered image
class Renderer{
public:

  static Renderer* getInstance();

  void Init(int argc, char **argv);
  void Run();
  void Draw();

private:
  Renderer();
  Renderer(Renderer&);
  Renderer& operator=(Renderer&);
  ~Renderer();

  void renderRectangle();
  Rect getNextRenderRectangle();

  std::vector<Scene*> scenes;
  int CurrentScene;

  static Renderer* Instance;

  //Variables for multithreaded rendering
  std::vector<std::thread> renderThreads;

  int currentRectIndex;
};


inline void onDisplay() {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Renderer::getInstance()->Draw();

  glutSwapBuffers();
}

inline void onIdle() {
  Renderer::getInstance()->Run();
}

#endif // Renderer_h__