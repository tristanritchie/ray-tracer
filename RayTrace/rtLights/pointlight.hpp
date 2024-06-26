/* ***********************************************************
        pointlight.hpp

        The point light class definition - A class for handling point
        lights.

        This file forms part of the RayTrace project as described
        in the series of videos on the QuantitativeBytes YouTube
        channel.

        This code corresponds specifically to Episode 6 of the series,
        which may be found here:
        https://youtu.be/9K9ZYq6KgFY

        The whole series may be found on the QuantitativeBytes
        YouTube channel at:
        www.youtube.com/c/QuantitativeBytes

        GPLv3 LICENSE
        Copyright (c) 2021 Michael Bennett

***********************************************************/
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

namespace RT
{
class PointLight : public LightBase
{
public:
  // The default constructor.
  PointLight();

  // Override the default destructor.
  virtual ~PointLight() override;

  // Function to compute illumination.
  virtual bool ComputeIllumination(
      const rtVector<double>& intPoint, const rtVector<double>& localNormal,
      const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
      const std::shared_ptr<RT::ObjectBase>& currentObject,
      rtVector<double>& color, double& intensity) override;
};
} // namespace RT

#endif
