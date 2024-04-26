#include "checker.hpp"

// Constructor / destructor.
RT::Texture::Checker::Checker()
{
  m_color1 = rtVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}};
  m_color2 = rtVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}};
}

RT::Texture::Checker::~Checker() {}

// Function to return the color.
rtVector<double>
RT::Texture::Checker::GetColor(const rtVector<double>& uvCoords)
{
  // Apply the local transform to the (u,v) coordinates.
  rtVector<double> inputLoc = uvCoords;
  rtVector<double> newLoc = ApplyTransform(inputLoc);
  double newU = newLoc.GetElement(0);
  double newV = newLoc.GetElement(1);

  rtVector<double> localColor{4};
  int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));

  if ((check % 2) == 0)
  {
    localColor = m_color1;
  }
  else
  {
    localColor = m_color2;
  }

  return localColor;
}

// Function to set the colors.
void RT::Texture::Checker::SetColor(const rtVector<double>& inputColor1,
                                    const rtVector<double>& inputColor2)
{
  m_color1 = inputColor1;
  m_color2 = inputColor2;
}
