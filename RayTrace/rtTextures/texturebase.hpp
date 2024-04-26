#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include "../ray.hpp"
#include "../rtLinAlg/rtMatrix.h"
#include "../rtLinAlg/rtVector.h"
#include <memory>

namespace RT
{
namespace Texture
{
class TextureBase
{
public:
  // Constructor / destructor.
  TextureBase();
  virtual ~TextureBase();

  // Function to retrun the color at a given point in the (u,v) coordinate
  // system. Note that the color is returned as a 4-dimensional vector (RGBA).
  virtual rtVector<double> GetColor(const rtVector<double>& uvCoords);

  // Function to set transform.
  void SetTransform(const rtVector<double>& translation, const double& rotation,
                    const rtVector<double>& scale);

  // Function to blend RGBA colors, returning a 3-dimensional (RGB) result.
  static rtVector<double>
  BlendColors(const std::vector<rtVector<double>>& inputColorList);

  // Function to apply the local transform to the given input vector.
  rtVector<double> ApplyTransform(const rtVector<double>& inputVector);

private:
private:
  // Initialise the transform matrix to the identity matrix.
  rtMatrix2<double> m_transformMatrix{
      3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
};
} // namespace Texture
} // namespace RT

#endif
