#include "Plane.h"

#include "Intersection.h"

Intersection Plane::getIntersection(Ray inRay)
{
  Intersection tempIntersection;

  float sum = normal * pos;
  sum = sum - inRay.startPos * normal;

  tempIntersection.distance = sum / (normal * inRay.directionVec);

  tempIntersection.setIntersectionPoint(inRay, tempIntersection.distance);

  if (tempIntersection.distance > EPSILON){
    tempIntersection.intersectingObject = this;
    tempIntersection.isValid = true;

    return tempIntersection;
  }

  tempIntersection.isValid = false;
  return tempIntersection;
}

Vector3D Plane::getNormal(Intersection)
{
  return normal;
}

Plane::Plane(Vector3D inPos, Vector3D inNormal, Material inMaterial)
{
  pos = inPos;
  normal = inNormal.getNormalized();

  mat = inMaterial;
}
