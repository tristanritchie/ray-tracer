#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include "../qbLinAlg/qbVector.h"
#include "../qbPrimatives/objectbase.hpp"
#include "../ray.hpp"
#include <memory>

namespace RT
{
class LightBase
{
public:
  // Constructor / destructor.
  LightBase();
  virtual ~LightBase();

  // Function to compute illumination contribution.
  virtual bool ComputeIllumination(
      const qbVector<double>& intPoint, const qbVector<double>& localNormal,
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::shared_ptr<RT::ObjectBase>& currentObject,
      qbVector<double>& color, double& intensity);

public:
  qbVector<double> m_color{3};
  qbVector<double> m_location{3};
  double m_intensity;
};
} // namespace RT

#endif
