#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../gtfm.hpp"
#include "../ray.hpp"
#include "../rtLinAlg/rtVector.h"
#include <memory>

namespace RT
{
/* Forward-declare the material base class. This will be
        overriden later. */
class MaterialBase;

class ObjectBase
{
public:
  // Constructor and destructor.
  ObjectBase();
  virtual ~ObjectBase();

  // Function to test for intersections.
  virtual bool TestIntersection(const Ray& castRay, rtVector<double>& intPoint,
                                rtVector<double>& localNormal,
                                rtVector<double>& localColor);

  // Function to set the transform matrix.
  void SetTransformMatrix(const RT::GTform& transformMatrix);

  // Function to test whether two floating-point numbers are close to being
  // equal.
  bool CloseEnough(const double f1, const double f2);

  // Function to assign a material.
  bool AssignMaterial(const std::shared_ptr<RT::MaterialBase>& objectMaterial);

  // Public member variables.
public:
  // The base colour of the object.
  rtVector<double> m_baseColor{3};

  // The geometric transform applied to the object.
  RT::GTform m_transformMatrix;

  // A reference to the material assigned to this object.
  std::shared_ptr<RT::MaterialBase> m_pMaterial;

  // A flag to indicate whether this object has a material or not.
  bool m_hasMaterial = false;

  // Store the (u,v) coordinates from a detected intersection.
  rtVector<double> m_uvCoords{2};
};
} // namespace RT

#endif
