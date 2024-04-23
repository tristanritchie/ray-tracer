#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace RT
{
class ObjSphere : public ObjectBase
{
public:
  /* The default constructor.
          Note that this will define a unit sphere at the origin. */
  ObjSphere();

  // Override the destructor.
  virtual ~ObjSphere() override;

  // Override the function to test for intersections.
  virtual bool TestIntersection(const RT::Ray& castRay,
                                qbVector<double>& intPoint,
                                qbVector<double>& localNormal,
                                qbVector<double>& localColor) override;

private:
};
} // namespace RT

#endif
