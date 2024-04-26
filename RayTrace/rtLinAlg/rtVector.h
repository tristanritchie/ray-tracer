// This file is part of the rtLinAlg linear algebra library.
// Copyright (c) 2021 Michael Bennett
// MIT license

#ifndef rtVector_H
#define rtVector_H

/* *************************************************************************************************

        rtVector

        Class to provide capability to handle vectors.

        Created as part of the rtLinAlg linear algebra library, which is
intended to be primarily for educational purposes. For more details, see the
corresponding videos on the QuantitativeBytes YouTube channel at:

        www.youtube.com/c/QuantitativeBytes

*************************************************************************************************
*/

#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <vector>

template <class T>
class rtVector
{
public:
  // Define the various constructors.
  // Default.
  rtVector();

  // With a single integer specifying the number of dimensions.
  rtVector(int numDims);

  // With input data (std::vector).
  rtVector(std::vector<T> inputData);

  // And the destructor.
  ~rtVector();

  // Functions to return parameters of the vector.
  int GetNumDims() const;

  // Functions to handle elements of the vector.
  T GetElement(int index) const;
  void SetElement(int index, T value);

  // Functions to perform computations on the vector.
  // Return the length of the vector.
  T norm();

  // Return a normalized copy of the vector.
  rtVector<T> Normalized();

  // Normalize the vector in place.
  void Normalize();

  // Overloaded operators.
  rtVector<T> operator+(const rtVector<T>& rhs) const;
  rtVector<T> operator-(const rtVector<T>& rhs) const;
  rtVector<T> operator*(const T& rhs) const;

  // Friend functions.
  template <class U>
  friend rtVector<U> operator*(const U& lhs, const rtVector<U>& rhs);

  // Static functions.
  static T dot(const rtVector<T>& a, const rtVector<T>& b);
  static rtVector<T> cross(const rtVector<T>& a, const rtVector<T>& b);

private:
  std::vector<T> m_vectorData;
  int m_nDims;
};

template <class T>
rtVector<T>::rtVector()
{
  m_nDims = 0;
  m_vectorData = std::vector<T>();
}

template <class T>
rtVector<T>::rtVector(int numDims)
{
  m_nDims = numDims;
  m_vectorData = std::vector<T>(numDims, static_cast<T>(0.0));
}

template <class T>
rtVector<T>::rtVector(std::vector<T> inputData)
{
  m_nDims = inputData.size();
  m_vectorData = inputData;
}

template <class T>
rtVector<T>::~rtVector()
{
  // For now, we don't need to do anything in the destructor.
}

template <class T>
int rtVector<T>::GetNumDims() const
{
  return m_nDims;
}

template <class T>
T rtVector<T>::GetElement(int index) const
{
  return m_vectorData[index];
}

template <class T>
void rtVector<T>::SetElement(int index, T value)
{
  m_vectorData[index] = value;
}

// Compute the length of the vector,known as the 'norm'.
template <class T>
T rtVector<T>::norm()
{
  T cumulativeSum = static_cast<T>(0.0);
  for (int i = 0; i < m_nDims; ++i)
    cumulativeSum += (m_vectorData.at(i) * m_vectorData.at(i));

  return sqrt(cumulativeSum);
}

// Return a normalized copy of the vector.
template <class T>
rtVector<T> rtVector<T>::Normalized()
{
  // Compute the vector norm.
  T vecNorm = this->norm();

  // Compute the normalized version of the vector.
  rtVector<T> result(m_vectorData);
  return result * (static_cast<T>(1.0) / vecNorm);
}

// Normalize the vector in place.
template <class T>
void rtVector<T>::Normalize()
{
  // Compute the vector norm.
  T vecNorm = this->norm();

  // Compute the elements of the normalized version of the vector.
  for (int i = 0; i < m_nDims; ++i)
  {
    T temp = m_vectorData.at(i) * (static_cast<T>(1.0) / vecNorm);
    m_vectorData.at(i) = temp;
  }
}

template <class T>
rtVector<T> rtVector<T>::operator+(const rtVector<T>& rhs) const
{
  // Check that the number of dimensions match.
  if (m_nDims != rhs.m_nDims)
    throw std::invalid_argument("Vector dimensions do not match.");

  std::vector<T> resultData;
  for (int i = 0; i < m_nDims; ++i)
    resultData.push_back(m_vectorData.at(i) + rhs.m_vectorData.at(i));

  rtVector<T> result(resultData);
  return result;
}

template <class T>
rtVector<T> rtVector<T>::operator-(const rtVector<T>& rhs) const
{
  // Check that the number of dimensions match.
  if (m_nDims != rhs.m_nDims)
    throw std::invalid_argument("Vector dimensions do not match.");

  std::vector<T> resultData;
  for (int i = 0; i < m_nDims; ++i)
    resultData.push_back(m_vectorData.at(i) - rhs.m_vectorData.at(i));

  rtVector<T> result(resultData);
  return result;
}

template <class T>
rtVector<T> rtVector<T>::operator*(const T& rhs) const
{
  // Perform scalar multiplication.
  std::vector<T> resultData;
  for (int i = 0; i < m_nDims; ++i)
    resultData.push_back(m_vectorData.at(i) * rhs);

  rtVector<T> result(resultData);
  return result;
}

template <class T>
rtVector<T> operator*(const T& lhs, const rtVector<T>& rhs)
{
  // Perform scalar multiplication.
  std::vector<T> resultData;
  for (int i = 0; i < rhs.m_nDims; ++i)
    resultData.push_back(lhs * rhs.m_vectorData.at(i));

  rtVector<T> result(resultData);
  return result;
}

template <class T>
T rtVector<T>::dot(const rtVector<T>& a, const rtVector<T>& b)
{
  // Check that the number of dimensions match.
  if (a.m_nDims != b.m_nDims)
    throw std::invalid_argument(
        "Vector dimensions must match for the dot-product to be computed.");

  // Compute the dot product.
  T cumulativeSum = static_cast<T>(0.0);
  for (int i = 0; i < a.m_nDims; ++i)
    cumulativeSum += a.m_vectorData.at(i) * b.m_vectorData.at(i);

  return cumulativeSum;
}

template <class T>
rtVector<T> rtVector<T>::cross(const rtVector<T>& a, const rtVector<T>& b)
{
  // Check that the number of dimensions match.
  if (a.m_nDims != b.m_nDims)
    throw std::invalid_argument(
        "Vector dimensions must match for the cross-product to be computed.");

  // Check that the number of dimensions is 3.
  /* Although the cross-product is also defined for 7 dimensions, we are
          not going to consider that case at this time. */
  if (a.m_nDims != 3)
    throw std::invalid_argument("The cross-product can only be computed for "
                                "three-dimensional vectors.");

  // Compute the cross product.
  std::vector<T> resultData;
  resultData.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) -
                       (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
  resultData.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) -
                         (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
  resultData.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) -
                       (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

  rtVector<T> result(resultData);
  return result;
}

#endif
