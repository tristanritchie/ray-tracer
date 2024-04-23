#ifndef SCENE_H
#define SCENE_H

#include "./qbLights/pointlight.hpp"
#include "./qbPrimatives/cone.hpp"
#include "./qbPrimatives/cylinder.hpp"
#include "./qbPrimatives/objplane.hpp"
#include "./qbPrimatives/objsphere.hpp"
#include "camera.hpp"
#include "image.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

namespace RT
{
class Scene
{
public:
  // The default constructor.
  Scene();

  // Function to perform the rendering.
  bool Render(Image& outputImage);

  // Function to cast a ray into the scene.
  bool CastRay(RT::Ray& castRay, std::shared_ptr<RT::ObjectBase>& closestObject,
               qbVector<double>& closestIntPoint,
               qbVector<double>& closestLocalNormal,
               qbVector<double>& closestLocalColor);

  // Private functions.
private:
  // Private members.
private:
  // The camera that we will use.
  RT::Camera m_camera;

  // The list of objects in the scene.
  std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;

  // The list of lights in the scene.
  std::vector<std::shared_ptr<RT::LightBase>> m_lightList;
};
} // namespace RT

#endif
