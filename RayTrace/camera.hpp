#ifndef CAMERA_H
#define CAMERA_H

#include "./rtLinAlg/rtVector.h"
#include "ray.hpp"

namespace RT
{
class Camera
{
public:
  // The default constructor.
  Camera();

  // Functions to set camera parameters.
  void SetPosition(const rtVector<double>& newPosition);
  void SetLookAt(const rtVector<double>& newLookAt);
  void SetUp(const rtVector<double>& upVector);
  void SetLength(double newLength);
  void SetHorzSize(double newSize);
  void SetAspect(double newAspect);

  // Functions to return camera parameters.
  rtVector<double> GetPosition();
  rtVector<double> GetLookAt();
  rtVector<double> GetUp();
  rtVector<double> GetU();
  rtVector<double> GetV();
  rtVector<double> GetScreenCentre();
  double GetLength();
  double GetHorzSize();
  double GetAspect();

  // Function to generate a ray.
  bool GenerateRay(float proScreenX, float proScreenY, RT::Ray& cameraRay);

  // Function to update the camera geometry.
  void UpdateCameraGeometry();

private:
  rtVector<double> m_cameraPosition{3};
  rtVector<double> m_cameraLookAt{3};
  rtVector<double> m_cameraUp{3};
  double m_cameraLength;
  double m_cameraHorzSize;
  double m_cameraAspectRatio;

  rtVector<double> m_alignmentVector{3};
  rtVector<double> m_projectionScreenU{3};
  rtVector<double> m_projectionScreenV{3};
  rtVector<double> m_projectionScreenCentre{3};
};
} // namespace RT

#endif
