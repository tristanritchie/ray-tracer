#ifndef CHECKER_H
#define CHECKER_H

#include "texturebase.hpp"

namespace RT
{
namespace Texture
{
class Checker : public TextureBase
{
public:
  // Constructor / destructor.
  Checker();
  virtual ~Checker() override;

  // Function to return the color.
  virtual rtVector<double> GetColor(const rtVector<double>& uvCoords) override;

  // Function to set the colors.
  void SetColor(const rtVector<double>& inputColor1,
                const rtVector<double>& inputColor2);

private:
  rtVector<double> m_color1{4};
  rtVector<double> m_color2{4};
};
} // namespace Texture
} // namespace RT

#endif
