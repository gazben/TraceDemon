#include <iostream>

#include "Renderer.h"
#include "Rectangle.h"

Renderer* Renderer::Instance = NULL;

std::mutex RunMutex;
void Renderer::Run()
{
  //Thread init
  for (int i = 0; i < THREAD_COUNT; ++i){
    renderThreads.push_back(std::thread([&](){
    renderRectangle();
    }));
  }

  for (auto& thread : renderThreads){
    thread.join();
  }
  std::cout << "Render ended with " << renderThreads.size() << "threads" << std::endl;
  renderThreads.clear();
}

void Renderer::Init(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("TraceDaemon - Progkonf2014");

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glutDisplayFunc(onDisplay);
  glutIdleFunc(onIdle);
  glutKeyboardFunc(onKeyboard);
  glutKeyboardUpFunc(onKeyboardUp);
  glutMotionFunc(onMouseMotion);

  onInitialization();

  //Load the scenes
  scenes.push_back(new Scene());
  scenes[0]->LoadObj(".\\Resources\\Cube.obj", ".\\Resources\\Cube3.mtl");
  CurrentScene = 0;

  currentRectIndex = 0;

  glutMainLoop();
}

Renderer& Renderer::operator=(Renderer&)
{
  return *this;
}

Renderer::Renderer(Renderer&)
{
}

Renderer::Renderer()
{
}

Renderer* Renderer::getInstance()
{
  if (!Instance)
    Instance = new Renderer();

  return Instance;
}

Renderer::~Renderer()
{
  for (int i = 0; i < scenes.size(); i++)
  {
    delete scenes[i];
  }
}

std::mutex RectangleLock;
Rect Renderer::getNextRenderRectangle()
{
  RectangleLock.lock();

  int RectIndex = currentRectIndex;
  currentRectIndex++;

  RectangleLock.unlock();

  //rect y,x position on the sreen
  int Xpos;
  int Ypos;

  Coordinate2D RectDownLeft;
  Coordinate2D RectUpRight;

  Ypos = RectIndex / RENDER_RECTANGLE_COUNT_SIDE;
  Xpos = RectIndex - (Ypos * RENDER_RECTANGLE_COUNT_SIDE);

  //FIXME - supprt all resolutions
  RectDownLeft.x = (SCREENWIDTH / RENDER_RECTANGLE_COUNT_SIDE) * Xpos;
  RectDownLeft.y = (SCREENHEIGHT / RENDER_RECTANGLE_COUNT_SIDE) * Ypos;

  RectUpRight.x = (SCREENWIDTH / RENDER_RECTANGLE_COUNT_SIDE) * (Xpos + 1);
  RectUpRight.y = (SCREENHEIGHT / RENDER_RECTANGLE_COUNT_SIDE) * (Ypos + 1);

  if ((Xpos % (RENDER_RECTANGLE_COUNT_SIDE - 1)) == 0)
    RectUpRight.x += SCREENWIDTH % RENDER_RECTANGLE_COUNT_SIDE;

  if (Ypos == RENDER_RECTANGLE_COUNT_SIDE - 1)
    RectUpRight.y += SCREENHEIGHT % RENDER_RECTANGLE_COUNT_SIDE;

  return Rect(RectDownLeft, RectUpRight);
}

void Renderer::renderRectangle()
{
  Rect rect = getNextRenderRectangle();

  if (currentRectIndex > (RENDER_RECTANGLE_COUNT_SIDE * RENDER_RECTANGLE_COUNT_SIDE))
    return;
  else if (rect.UpRigh.x > SCREENWIDTH)
    return;
  else if (rect.UpRigh.y > SCREENHEIGHT)
    return;

  for (int y = rect.DownLeft.y; y < rect.UpRigh.y; y++){
    for (int x = rect.DownLeft.x; x < rect.UpRigh.x; x++){
      scenes[CurrentScene]->Draw(x, y);
     // std::cout << "Pixel: " << "X: " << x << " Y: " << y << " rendered on thread"<< std::this_thread::get_id() << std::endl;
    }
  }
  std::cout << "Rect render ended!" << std::endl;
  renderRectangle();
}

void Renderer::Draw()
{
  glDrawPixels(SCREENHEIGHT , SCREENWIDTH , GL_RGB, GL_FLOAT, scenes[CurrentScene]->image );
}
