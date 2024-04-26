#ifndef GTFM_H
#define GTFM_H

#include "./rtLinAlg/rtMatrix.h"
#include "./rtLinAlg/rtVector.h"
#include "ray.hpp"

namespace RT
{
// Define direction flag values.
constexpr bool FWDTFORM = true;
constexpr bool BCKTFORM = false;

class GTform
{
public:
  // Constructor & destructor.
  GTform();
  ~GTform();

  // Construct from three vectors.
  GTform(const rtVector<double>& translation, const rtVector<double>& rotation,
         const rtVector<double>& scale);

  // Construct from a pair of matrices.
  GTform(const rtMatrix2<double>& fwd, const rtMatrix2<double>& bck);

  // Function to set translation, rotation and scale components.
  void SetTransform(const rtVector<double>& translation,
                    const rtVector<double>& rotation,
                    const rtVector<double>& scale);

  // Functions to return the transform matrices.
  rtMatrix2<double> GetForward();
  rtMatrix2<double> GetBackward();

  // Function to apply the transform.
  RT::Ray Apply(const RT::Ray& inputRay, bool dirFlag);
  rtVector<double> Apply(const rtVector<double>& inputVector, bool dirFlag);

  // Overload operators.
  friend GTform operator*(const RT::GTform& lhs, const RT::GTform& rhs);

  // Overload the assignment operator.
  GTform operator=(const GTform& rhs);

  // Function to print transform matrix to STDOUT.
  void PrintMatrix(bool dirFlag);

  // Function to allow printing of vectors.
  static void PrintVector(const rtVector<double>& vector);

private:
  void Print(const rtMatrix2<double>& matrix);

private:
  rtMatrix2<double> m_fwdtfm{4, 4};
  rtMatrix2<double> m_bcktfm{4, 4};
};
} // namespace RT

#endif
