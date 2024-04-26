#include "lightbase.hpp"

// Constructor.
RT::LightBase::LightBase() {}

// Destructor.
RT::LightBase::~LightBase() {}

// Function to compute illumination.
bool RT::LightBase::ComputeIllumination(
    const rtVector<double>& intPoint, const rtVector<double>& localNormal,
    const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
    const std::shared_ptr<RT::ObjectBase>& currentObject,
    rtVector<double>& color, double& intensity)
{
  return false;
}
