// This file is part of the rtLinAlg linear algebra library.
// Copyright (c) 2021 Michael Bennett
// MIT license

#ifndef QBLSQ_H
#define QBLSQ_H

/* *************************************************************************************************

        rtLSQ

        Function to solve a system of linear equations using a least squares
   approach to handle systems where there are more equations (observations) than
   unknowns. Assumes that the system is in the form of y = X*beta.

        *** INPUTS ***

        Xin		rtMatrix2<T>		The matrix of independent
   variables (X in the above equation). yin		rtVector<T>
   The vector of dependent variables (y in the above equation). result
   rtVector<T>		The vector of unknown parameters (beta in the above
   equation). The final solution is returned in this vector.

        *** OUTPUTS ***

        INT				Flag indicating success or failure of
   the process. 1 Indicates success. -1 indicates failure due to there being no
   computable inverse.

        Created as part of the rtLinAlg linear algebra library, which is
   intended to be primarily for educational purposes. For more details, see the
   corresponding videos on the QuantitativeBytes YouTube channel at:

        www.youtube.com/c/QuantitativeBytes

        *************************************************************************************************
 */

#include "rtMatrix.h"
#include "rtVector.h"
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <vector>

// Define error codes.
constexpr int QBLSQ_NOINVERSE = -1;

// The rtLSQ function.
template <typename T>
int rtLSQ(const rtMatrix2<T>& Xin, const rtVector<T>& yin, rtVector<T>& result)
{
  // Firstly, make a copy of X and y.
  rtMatrix2<T> X = Xin;
  rtVector<T> y = yin;

  // Compute the tranpose of X.
  rtMatrix2<T> XT = X.Transpose();

  // Compute XTX.
  rtMatrix2<T> XTX = XT * X;

  // Compute the inverse of this.
  if (!XTX.Inverse())
  {
    // We were unable to compute the inverse.
    return QBLSQ_NOINVERSE;
  }

  // Multiply the inverse by XT.
  rtMatrix2<T> XTXXT = XTX * XT;

  // And multiply by y to get the final result.
  result = XTXXT * y;

  return 1;
}

#endif
