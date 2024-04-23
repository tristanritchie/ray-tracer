#ifndef GTFM_H
#define GTFM_H

#include "./qbLinAlg/qbMatrix.h"
#include "./qbLinAlg/qbVector.h"
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
  GTform(const qbVector<double>& translation, const qbVector<double>& rotation,
         const qbVector<double>& scale);

  // Construct from a pair of matrices.
  GTform(const qbMatrix2<double>& fwd, const qbMatrix2<double>& bck);

  // Function to set translation, rotation and scale components.
  void SetTransform(const qbVector<double>& translation,
                    const qbVector<double>& rotation,
                    const qbVector<double>& scale);

  // Functions to return the transform matrices.
  qbMatrix2<double> GetForward();
  qbMatrix2<double> GetBackward();

  // Function to apply the transform.
  RT::Ray Apply(const RT::Ray& inputRay, bool dirFlag);
  qbVector<double> Apply(const qbVector<double>& inputVector, bool dirFlag);

  // Overload operators.
  friend GTform operator*(const RT::GTform& lhs, const RT::GTform& rhs);

  // Overload the assignment operator.
  GTform operator=(const GTform& rhs);

  // Function to print transform matrix to STDOUT.
  void PrintMatrix(bool dirFlag);

  // Function to allow printing of vectors.
  static void PrintVector(const qbVector<double>& vector);

private:
  void Print(const qbMatrix2<double>& matrix);

private:
  qbMatrix2<double> m_fwdtfm{4, 4};
  qbMatrix2<double> m_bcktfm{4, 4};
};
} // namespace RT

#endif
