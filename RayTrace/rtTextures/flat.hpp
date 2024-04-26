#ifndef FLAT_H
#define FLAT_H

#include "texturebase.hpp"

namespace RT
{
namespace Texture
{
class Flat : public TextureBase
{
public:
  // Constructor / destructor.
  Flat();
  virtual ~Flat() override;

  // Function to return the color.
  virtual rtVector<double> GetColor(const rtVector<double>& uvCoords) override;

  // Function to set the color.
  void SetColor(const rtVector<double>& inputColor);

private:
  rtVector<double> m_color{4};
};
} // namespace Texture
} // namespace RT

#endif
