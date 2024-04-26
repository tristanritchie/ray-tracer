#include "simplematerial.hpp"

RT::SimpleMaterial::SimpleMaterial() {}

RT::SimpleMaterial::~SimpleMaterial() {}

// Function to return the color.
rtVector<double> RT::SimpleMaterial::ComputeColor(
    const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
    const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
    const std::shared_ptr<RT::ObjectBase>& currentObject,
    const rtVector<double>& intPoint, const rtVector<double>& localNormal,
    const RT::Ray& cameraRay)
{
  // Define the initial material colors.
  rtVector<double> matColor{3};
  rtVector<double> refColor{3};
  rtVector<double> difColor{3};
  rtVector<double> spcColor{3};

  // Compute the diffuse component.
  if (!m_hasTexture)
    difColor = ComputeDiffuseColor(objectList, lightList, currentObject,
                                   intPoint, localNormal, m_baseColor);
  else
    difColor = ComputeDiffuseColor(
        objectList, lightList, currentObject, intPoint, localNormal,
        m_textureList.at(0)->GetColor(currentObject->m_uvCoords));

  // Compute the reflection component.
  if (m_reflectivity > 0.0)
    refColor = ComputeReflectionColor(objectList, lightList, currentObject,
                                      intPoint, localNormal, cameraRay);

  // Combine reflection and diffuse components.
  matColor = (refColor * m_reflectivity) + (difColor * (1 - m_reflectivity));

  // Compute the specular component.
  if (m_shininess > 0.0)
    spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal,
                               cameraRay);

  // Add the specular component to the final color.
  matColor = matColor + spcColor;

  return matColor;
}

// Function to compute the specular highlights.
rtVector<double> RT::SimpleMaterial::ComputeSpecular(
    const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
    const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
    const rtVector<double>& intPoint, const rtVector<double>& localNormal,
    const RT::Ray& cameraRay)
{
  rtVector<double> spcColor{3};
  double red = 0.0;
  double green = 0.0;
  double blue = 0.0;

  // Loop through all of the lights in the scene.
  for (auto currentLight : lightList)
  {
    /* Check for intersections with all objects in the scene. */
    double intensity = 0.0;

    // Construct a vector pointing from the intersection point to the light.
    rtVector<double> lightDir =
        (currentLight->m_location - intPoint).Normalized();

    // Compute a start point.
    rtVector<double> startPoint = intPoint + (lightDir * 0.001);

    // Construct a ray from the point of intersection to the light.
    RT::Ray lightRay(startPoint, startPoint + lightDir);

    /* Loop through all objects in the scene to check if any
            obstruct light from this source. */
    rtVector<double> poi{3};
    rtVector<double> poiNormal{3};
    rtVector<double> poiColor{3};
    bool validInt = false;
    for (auto sceneObject : objectList)
    {
      validInt =
          sceneObject->TestIntersection(lightRay, poi, poiNormal, poiColor);
      if (validInt)
        break;
    }

    /* If no intersections were found, then proceed with
            computing the specular component. */
    if (!validInt)
    {
      // Compute the reflection vector.
      rtVector<double> d = lightRay.m_lab;
      rtVector<double> r =
          d - (2 * rtVector<double>::dot(d, localNormal) * localNormal);
      r.Normalize();

      // Compute the dot product.
      rtVector<double> v = cameraRay.m_lab;
      v.Normalize();
      double dotProduct = rtVector<double>::dot(r, v);

      // Only proceed if the dot product is positive.
      if (dotProduct > 0.0)
      {
        intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
      }
    }

    red += currentLight->m_color.GetElement(0) * intensity;
    green += currentLight->m_color.GetElement(1) * intensity;
    blue += currentLight->m_color.GetElement(2) * intensity;
  }

  spcColor.SetElement(0, red);
  spcColor.SetElement(1, green);
  spcColor.SetElement(2, blue);
  return spcColor;
}
