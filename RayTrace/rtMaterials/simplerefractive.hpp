#ifndef SIMPLEREFRACTIVE_H
#define SIMPLEREFRACTIVE_H

#include "materialbase.hpp"

namespace RT
{
class SimpleRefractive : public MaterialBase
{
public:
  // Constructor / destructor.
  SimpleRefractive();
  virtual ~SimpleRefractive() override;

  // Function to return the color.
  virtual rtVector<double>
  ComputeColor(const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
               const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
               const std::shared_ptr<RT::ObjectBase>& currentObject,
               const rtVector<double>& intPoint,
               const rtVector<double>& localNormal,
               const RT::Ray& cameraRay) override;

  // Function to compute specular highlights.
  rtVector<double> ComputeSpecular(
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
      const rtVector<double>& intPoint, const rtVector<double>& localNormal,
      const RT::Ray& cameraRay);

  // Function to compute translucency.
  rtVector<double> ComputeTranslucency(
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
      const std::shared_ptr<RT::ObjectBase>& currentObject,
      const rtVector<double>& intPoint, const rtVector<double>& localNormal,
      const RT::Ray& incidentRay);

public:
  rtVector<double> m_baseColor{std::vector<double>{1.0, 0.0, 1.0}};
  double m_reflectivity = 0.0;
  double m_shininess = 0.0;
  double m_translucency = 0.0;
  double m_ior = 1.0;
};
} // namespace RT

#endif
