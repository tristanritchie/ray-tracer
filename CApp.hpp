#ifndef CAPP_H
#define CAPP_H

#include "./RayTrace/camera.hpp"
#include "./RayTrace/image.hpp"
#include "./RayTrace/rtTextures/checker.hpp"
#include "./RayTrace/rtTextures/flat.hpp"
#include "./RayTrace/rtTextures/image.hpp"
#include "./RayTrace/scene.hpp"
#include <SDL2/SDL.h>

class CApp
{
public:
  CApp();

  int OnExecute();
  bool OnInit();
  void OnEvent(SDL_Event* event);
  void OnLoop();
  void OnRender();
  void OnExit();

private:
  void PrintVector(const rtVector<double>& inputVector);

private:
  // An instance of the Image class to store the image.
  Image m_image;

  // An instance of the scene class.
  RT::Scene m_scene;

  // SDL2 stuff.
  bool isRunning;
  SDL_Window* pWindow;
  SDL_Renderer* pRenderer;
};

#endif
