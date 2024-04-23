#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

// Default constructor.
qbRT::ObjectBase::ObjectBase() {}

// The destructor.
qbRT::ObjectBase::~ObjectBase() {}

// Function to test for intersections.
bool qbRT::ObjectBase::TestIntersection(const Ray& castRay,
                                        qbVector<double>& intPoint,
                                        qbVector<double>& localNormal,
                                        qbVector<double>& localColor)
{
  return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform& transformMatrix)
{
  m_transformMatrix = transformMatrix;
}

// Function to assign a material.
bool qbRT::ObjectBase::AssignMaterial(
    const std::shared_ptr<qbRT::MaterialBase>& objectMaterial)
{
  m_pMaterial = objectMaterial;
  m_hasMaterial = true;
  return m_hasMaterial;
}

// Function to test whether two floating-point numbers are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
  return fabs(f1 - f2) < EPSILON;
}
