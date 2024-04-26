#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include "../ray.hpp"
#include "../rtLinAlg/rtVector.h"
#include "../rtPrimatives/objectbase.hpp"
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
      const rtVector<double>& intPoint, const rtVector<double>& localNormal,
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::shared_ptr<RT::ObjectBase>& currentObject,
      rtVector<double>& color, double& intensity);

public:
  rtVector<double> m_color{3};
  rtVector<double> m_location{3};
  double m_intensity;
};
} // namespace RT

#endif
