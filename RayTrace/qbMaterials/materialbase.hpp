#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include "../qbLights/lightbase.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../qbPrimatives/objectbase.hpp"
#include "../qbTextures/texturebase.hpp"
#include "../ray.hpp"
#include <memory>

namespace qbRT
{
class MaterialBase
{
public:
  MaterialBase();
  virtual ~MaterialBase();

  // Function to return the color of the material.
  virtual qbVector<double>
  ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>>& objectList,
               const std::vector<std::shared_ptr<qbRT::LightBase>>& lightList,
               const std::shared_ptr<qbRT::ObjectBase>& currentObject,
               const qbVector<double>& intPoint,
               const qbVector<double>& localNormal, const qbRT::Ray& cameraRay);

  // Function to compute diffuse color.
  static qbVector<double> ComputeDiffuseColor(
      const std::vector<std::shared_ptr<qbRT::ObjectBase>>& objectList,
      const std::vector<std::shared_ptr<qbRT::LightBase>>& lightList,
      const std::shared_ptr<qbRT::ObjectBase>& currentObject,
      const qbVector<double>& intPoint, const qbVector<double>& localNormal,
      const qbVector<double>& baseColor);

  // Function to compute the reflection color.
  qbVector<double> ComputeReflectionColor(
      const std::vector<std::shared_ptr<qbRT::ObjectBase>>& objectList,
      const std::vector<std::shared_ptr<qbRT::LightBase>>& lightList,
      const std::shared_ptr<qbRT::ObjectBase>& currentObject,
      const qbVector<double>& intPoint, const qbVector<double>& localNormal,
      const qbRT::Ray& incidentRay);

  // Function to cast a ray into the scene.
  bool CastRay(const qbRT::Ray& castRay,
               const std::vector<std::shared_ptr<qbRT::ObjectBase>>& objectList,
               const std::shared_ptr<qbRT::ObjectBase>& thisObject,
               std::shared_ptr<qbRT::ObjectBase>& closestObject,
               qbVector<double>& closestIntPoint,
               qbVector<double>& closestLocalNormal,
               qbVector<double>& closestLocalColor);

  // Function to assign a texture.
  void AssignTexture(
      const std::shared_ptr<qbRT::Texture::TextureBase>& inputTexture);

public:
  // Counter for the number of relection rays.
  inline static int m_maxReflectionRays;
  inline static int m_reflectionRayCount;

  // The ambient lighting conditions.
  inline static qbVector<double> m_ambientColor{
      std::vector<double>{1.0, 1.0, 1.0}};
  inline static double m_ambientIntensity = 0.2;

  // List of texures assigned to this material.
  std::vector<std::shared_ptr<qbRT::Texture::TextureBase>> m_textureList;

  // Flat to indicate whether at least one texture has been assigned.
  bool m_hasTexture = false;

private:
};
} // namespace qbRT

#endif
