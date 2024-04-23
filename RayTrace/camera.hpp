#ifndef CAMERA_H
#define CAMERA_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"

namespace RT
{
class Camera
{
public:
  // The default constructor.
  Camera();

  // Functions to set camera parameters.
  void SetPosition(const qbVector<double>& newPosition);
  void SetLookAt(const qbVector<double>& newLookAt);
  void SetUp(const qbVector<double>& upVector);
  void SetLength(double newLength);
  void SetHorzSize(double newSize);
  void SetAspect(double newAspect);

  // Functions to return camera parameters.
  qbVector<double> GetPosition();
  qbVector<double> GetLookAt();
  qbVector<double> GetUp();
  qbVector<double> GetU();
  qbVector<double> GetV();
  qbVector<double> GetScreenCentre();
  double GetLength();
  double GetHorzSize();
  double GetAspect();

  // Function to generate a ray.
  bool GenerateRay(float proScreenX, float proScreenY, RT::Ray& cameraRay);

  // Function to update the camera geometry.
  void UpdateCameraGeometry();

private:
  qbVector<double> m_cameraPosition{3};
  qbVector<double> m_cameraLookAt{3};
  qbVector<double> m_cameraUp{3};
  double m_cameraLength;
  double m_cameraHorzSize;
  double m_cameraAspectRatio;

  qbVector<double> m_alignmentVector{3};
  qbVector<double> m_projectionScreenU{3};
  qbVector<double> m_projectionScreenV{3};
  qbVector<double> m_projectionScreenCentre{3};
};
} // namespace RT

#endif
