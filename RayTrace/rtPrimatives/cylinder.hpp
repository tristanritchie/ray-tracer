#ifndef CYLINDER_H
#define CYLINDER_H

#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace RT
{
class Cylinder : public ObjectBase
{
public:
  // Default constructor.
  Cylinder();

  // Override the destructor.
  virtual ~Cylinder() override;

  // Override the function to test for intersections.
  virtual bool TestIntersection(const RT::Ray& castRay,
                                rtVector<double>& intPoint,
                                rtVector<double>& localNormal,
                                rtVector<double>& localColor) override;
};
} // namespace RT

#endif
