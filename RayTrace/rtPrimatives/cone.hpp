#ifndef CONE_H
#define CONE_H

#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace RT
{
class Cone : public ObjectBase
{
public:
  // Default constructor.
  Cone();

  // Override the destructor.
  virtual ~Cone() override;

  // Override the function to test for intersections.
  virtual bool TestIntersection(const RT::Ray& castRay,
                                rtVector<double>& intPoint,
                                rtVector<double>& localNormal,
                                rtVector<double>& localColor) override;
};
} // namespace RT

#endif
