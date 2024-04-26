#include "CApp.hpp"
#include "./RayTrace/rtLinAlg/rtVector.h"

// The constructor (default)
CApp::CApp()
{
  isRunning = true;
  pWindow = NULL;
  pRenderer = NULL;
}

bool CApp::OnInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    return false;
  }

  int xSize = 1280;
  int ySize = 720;

  pWindow =
      SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, xSize, ySize, SDL_WINDOW_SHOWN);

  if (pWindow != NULL)
  {
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

    // Intialize the Image instance.
    m_image.Initialize(xSize, ySize, pRenderer);

    // Set the background color to white.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    // Render the scene.
    m_scene.Render(m_image);

    // Setup a texture.
    /*RT::Texture::Image testTexture;
    testTexture.LoadImage("testImage.bmp");
    testTexture.SetTransform(	rtVector<double>{std::vector<double>{0.0, 0.0}},
                                                                                                            0.0,
                                                                                                            rtVector<double>{std::vector<double>{4.0, 4.0}}	);

    // Render the texture.
    for (int y=0; y<ySize; ++y)
    {
            for (int x=0; x<xSize; ++x)
            {
                    // Compute u,v
                    double u = (static_cast<double>(x) /
    (static_cast<double>(xSize) / 2.0)) - 1.0; double v =
    (static_cast<double>(y) / (static_cast<double>(ySize) / 2.0)) - 1.0;
                    rtVector<double> uvCoords {std::vector<double> {u, v}};

                    // Get the color from the texture.
                    rtVector<double> pixelColor =
    testTexture.GetColor(uvCoords);

                    // Update this pixel of the image.
                    m_image.SetPixel(x, y, pixelColor.GetElement(0),
    pixelColor.GetElement(1), pixelColor.GetElement(2));
            }
    } */

    // Display the image.
    m_image.Display();

    // Show the result.
    SDL_RenderPresent(pRenderer);
  }
  else
  {
    return false;
  }

  return true;
}

int CApp::OnExecute()
{
  SDL_Event event;

  if (OnInit() == false)
  {
    return -1;
  }

  while (isRunning)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      OnEvent(&event);
    }

    OnLoop();
    OnRender();
  }

  OnExit();
  return 0;
}

void CApp::OnEvent(SDL_Event* event)
{
  if (event->type == SDL_QUIT)
  {
    isRunning = false;
  }
}

void CApp::OnLoop() {}

void CApp::OnRender()
{
  // Set the background color to white.
  // SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
  // SDL_RenderClear(pRenderer);

  // Render the scene.
  // m_scene.Render(m_image);

  // Display the image.
  // m_image.Display();

  // Show the result.
  // SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
  // Tidy up SDL2 stuff.
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
  pWindow = NULL;
  SDL_Quit();
}

// PRIVATE FUNCTIONS.
void CApp::PrintVector(const rtVector<double>& inputVector)
{
  int nRows = inputVector.GetNumDims();
  for (int row = 0; row < nRows; ++row)
  {
    std::cout << std::fixed << std::setprecision(3)
              << inputVector.GetElement(row) << std::endl;
  }
}
