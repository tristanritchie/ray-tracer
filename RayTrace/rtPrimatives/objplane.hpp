#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace RT
{
class ObjPlane : public ObjectBase
{
public:
  // Default constructor.
  ObjPlane();

  // Override the destructor.
  virtual ~ObjPlane() override;

  // Override the function to test for intersections.
  virtual bool TestIntersection(const RT::Ray& castRay,
                                rtVector<double>& intPoint,
                                rtVector<double>& localNormal,
                                rtVector<double>& localColor) override;

private:
};
} // namespace RT

#endif
