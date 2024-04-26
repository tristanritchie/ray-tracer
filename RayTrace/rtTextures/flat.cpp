#include "flat.hpp"

// Constructor / destructor.
RT::Texture::Flat::Flat()
{
  m_color = rtVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}};
}

RT::Texture::Flat::~Flat() {}

// Function to return the color.
rtVector<double> RT::Texture::Flat::GetColor(const rtVector<double>& uvCoords)
{
  return m_color;
}

// Function to set the color.
void RT::Texture::Flat::SetColor(const rtVector<double>& inputColor)
{
  m_color = inputColor;
}
