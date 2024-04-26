#ifndef RAY_H
#define RAY_H

#include "./rtLinAlg/rtVector.h"

namespace RT
{
class Ray
{
public:
  Ray();
  Ray(const rtVector<double>& point1, const rtVector<double>& point2);

  rtVector<double> GetPoint1() const;
  rtVector<double> GetPoint2() const;

public:
  rtVector<double> m_point1{3};
  rtVector<double> m_point2{3};
  rtVector<double> m_lab{3};
};
} // namespace RT

#endif
