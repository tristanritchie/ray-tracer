#include "simplerefractive.hpp"

RT::SimpleRefractive::SimpleRefractive() {}

RT::SimpleRefractive::~SimpleRefractive() {}

// Function to return the color.
rtVector<double> RT::SimpleRefractive::ComputeColor(
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
  rtVector<double> trnColor{3};

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

  // Combine the reflection and diffuse components.
  matColor = (refColor * m_reflectivity) + (difColor * (1.0 - m_reflectivity));

  // Compute the refractive component.
  if (m_translucency > 0.0)
    trnColor = ComputeTranslucency(objectList, lightList, currentObject,
                                   intPoint, localNormal, cameraRay);

  // And combine with the current color.
  matColor = (trnColor * m_translucency) + (matColor * (1.0 - m_translucency));

  // And compute the specular component.
  if (m_shininess > 0.0)
    spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal,
                               cameraRay);

  // Finally, add the specular component.
  matColor = matColor + spcColor;

  return matColor;
}

// Function to compute the color due to translucency.
rtVector<double> RT::SimpleRefractive::ComputeTranslucency(
    const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
    const std::vector<std::shared_ptr<RT::LightBase>>& lightList,
    const std::shared_ptr<RT::ObjectBase>& currentObject,
    const rtVector<double>& intPoint, const rtVector<double>& localNormal,
    const RT::Ray& incidentRay)
{
  rtVector<double> trnColor{3};

  // Compute the refracted vector.
  rtVector<double> p = incidentRay.m_lab;
  p.Normalize();
  rtVector<double> tempNormal = localNormal;
  double r = 1.0 / m_ior;
  double c = -rtVector<double>::dot(tempNormal, p);
  if (c < 0.0)
  {
    tempNormal = tempNormal * -1.0;
    c = -rtVector<double>::dot(tempNormal, p);
  }

  rtVector<double> refractedVector =
      r * p +
      (r * c - sqrtf(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))) * tempNormal;

  // Construct the refracted ray.
  RT::Ray refractedRay(intPoint + (refractedVector * 0.01),
                       intPoint + refractedVector);

  // Test for secondary intersection with this object.
  std::shared_ptr<RT::ObjectBase> closestObject;
  rtVector<double> closestIntPoint{3};
  rtVector<double> closestLocalNormal{3};
  rtVector<double> closestLocalColor{3};
  rtVector<double> newIntPoint{3};
  rtVector<double> newLocalNormal{3};
  rtVector<double> newLocalColor{3};
  bool test = currentObject->TestIntersection(refractedRay, newIntPoint,
                                              newLocalNormal, newLocalColor);
  bool intersectionFound = false;
  RT::Ray finalRay;
  if (test)
  {
    // Compute the refracted vector.
    rtVector<double> p2 = refractedRay.m_lab;
    p2.Normalize();
    rtVector<double> tempNormal2 = newLocalNormal;
    double r2 = m_ior;
    double c2 = -rtVector<double>::dot(tempNormal2, p2);
    if (c2 < 0.0)
    {
      tempNormal2 = tempNormal2 * -1.0;
      c2 = -rtVector<double>::dot(tempNormal2, p2);
    }
    rtVector<double> refractedVector2 =
        r2 * p2 + (r2 * c2 - sqrtf(1.0 - pow(r2, 2.0) * (1.0 - pow(c2, 2.0)))) *
                      tempNormal2;

    // Compute the refracted ray.
    RT::Ray refractedRay2(newIntPoint + (refractedVector2 * 0.01),
                          newIntPoint + refractedVector2);

    // Cast this ray into the scene.
    intersectionFound =
        CastRay(refractedRay2, objectList, currentObject, closestObject,
                closestIntPoint, closestLocalNormal, closestLocalColor);
    finalRay = refractedRay2;
  }
  else
  {
    /* No secondary intersections were found, so continue the original refracted
     * ray. */
    intersectionFound =
        CastRay(refractedRay, objectList, currentObject, closestObject,
                closestIntPoint, closestLocalNormal, closestLocalColor);
    finalRay = refractedRay;
  }

  // Compute the color for closest object.
  rtVector<double> matColor{3};
  if (intersectionFound)
  {
    // Check if a material has been assigned.
    if (closestObject->m_hasMaterial)
    {
      matColor = closestObject->m_pMaterial->ComputeColor(
          objectList, lightList, closestObject, closestIntPoint,
          closestLocalNormal, finalRay);
    }
    else
    {
      matColor = RT::MaterialBase::ComputeDiffuseColor(
          objectList, lightList, closestObject, closestIntPoint,
          closestLocalNormal, closestObject->m_baseColor);
    }
  }
  else
  {
    // Leave matColor as it is.
  }

  trnColor = matColor;
  return trnColor;
}

// Function to compute the specular highlights.
rtVector<double> RT::SimpleRefractive::ComputeSpecular(
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
