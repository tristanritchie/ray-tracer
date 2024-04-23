#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "materialbase.hpp"

namespace RT
{
class SimpleMaterial : public MaterialBase
{
public:
  // Constructor / destructor.
  SimpleMaterial();
  virtual ~SimpleMaterial() override;

  // Function to return the color.
  virtual qbVector<double>
  ComputeColor(const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
               const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
               const std::shared_ptr<RT::ObjectBase>& currentObject,
               const qbVector<double>& intPoint,
               const qbVector<double>& localNormal,
               const RT::Ray& cameraRay) override;

  // Function to compute specular highlights.
  qbVector<double> ComputeSpecular(
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
      const qbVector<double>& intPoint, const qbVector<double>& localNormal,
      const RT::Ray& cameraRay);

public:
  qbVector<double> m_baseColor{std::vector<double>{1.0, 0.0, 1.0}};
  double m_reflectivity = 0.0;
  double m_shininess = 0.0;
};
} // namespace RT

#endif
