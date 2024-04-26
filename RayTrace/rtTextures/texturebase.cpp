#include "texturebase.hpp"
#include <cmath>

// Constructor / destructor.
RT::Texture::TextureBase::TextureBase() {}

RT::Texture::TextureBase::~TextureBase() {}

// Function to return the color at a given (U,V) location.
rtVector<double>
RT::Texture::TextureBase::GetColor(const rtVector<double>& uvCoords)
{
  // Setup the output vector.
  rtVector<double> outputColor{4};

  // Return the output.
  return outputColor;
}

// Function to set the transform matrix.
void RT::Texture::TextureBase::SetTransform(const rtVector<double>& translation,
                                            const double& rotation,
                                            const rtVector<double>& scale)
{
  // Build the transform matrix.
  rtMatrix2<double> rotationMatrix = {
      3, 3,
      std::vector<double>{cos(rotation), -sin(rotation), 0.0, sin(rotation),
                          cos(rotation), 0.0, 0.0, 0.0, 1.0}};

  rtMatrix2<double> scaleMatrix = {
      3, 3,
      std::vector<double>{scale.GetElement(0), 0.0, 0.0, 0.0,
                          scale.GetElement(1), 0.0, 0.0, 0.0, 1.0}};

  rtMatrix2<double> translationMatrix = {
      3, 3,
      std::vector<double>{1.0, 0.0, translation.GetElement(0), 0.0, 1.0,
                          translation.GetElement(1), 0.0, 0.0, 1.0}};

  // And combine to form the final transform matrix.
  m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

// Function to blend colors.
rtVector<double> RT::Texture::TextureBase::BlendColors(
    const std::vector<rtVector<double>>& inputColorList)
{
  // Setup the output color.
  rtVector<double> outputColor{3};

  // Return the output.
  return outputColor;
}

// Function to apply the transform.
rtVector<double>
RT::Texture::TextureBase::ApplyTransform(const rtVector<double>& inputVector)
{
  // Copy the input vector and modify to have three elements.
  rtVector<double> newInput{3};
  newInput.SetElement(0, inputVector.GetElement(0));
  newInput.SetElement(1, inputVector.GetElement(1));

  // Apply the transform.
  rtVector<double> result = m_transformMatrix * newInput;

  // Produce the output.
  rtVector<double> output{2};
  output.SetElement(0, result.GetElement(0));
  output.SetElement(1, result.GetElement(1));

  return output;
}
