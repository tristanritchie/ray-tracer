#include "flat.hpp"

// Constructor / destructor.
RT::Texture::Flat::Flat()
{
  m_color = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}};
}

RT::Texture::Flat::~Flat() {}

// Function to return the color.
qbVector<double> RT::Texture::Flat::GetColor(const qbVector<double>& uvCoords)
{
  return m_color;
}

// Function to set the color.
void RT::Texture::Flat::SetColor(const qbVector<double>& inputColor)
{
  m_color = inputColor;
}
