#include "Sphere.h"

#include "Intersection.h"

Vector3D Sphere::getNormal(Intersection intersection)
{
  Vector3D tempNormal(intersection.interSectionPoint - pos);

  return tempNormal.getNormalized();
}

Intersection Sphere::getIntersection(Ray ray)
{
  Intersection tempIntersection;
  float t1;
  float t2;

  float a = ray.directionVec * ray.directionVec;
  float b =
    2 * ray.directionVec.x *
    (ray.startPos.x - pos.x) +
    2 * ray.directionVec.y *
    (ray.startPos.y - pos.y) +
    2 * ray.directionVec.z * (ray.startPos.z - pos.z);
  float c = pos * pos + ray.startPos * ray.startPos - 2 * (pos * ray.startPos) - radius * radius;

  float discriminent = (b * b) - (4 * a * c);

  if (discriminent < EPSILON)
    tempIntersection.isValid = false;

  else
  {
    t1 = (-1.0 * b + sqrt(discriminent)) / (2.0 * a);
    t2 = (-1.0 * b - sqrt(discriminent)) / (2.0 * a);

    if (t2 < EPSILON && t1 >= EPSILON)
      tempIntersection.distance = t1;
    else
      tempIntersection.distance = (t1 < t2) ? t1 : t2;

    if (tempIntersection.distance > EPSILON){
      tempIntersection.isValid = true;
      tempIntersection.intersectingObject = this;

      tempIntersection.setIntersectionPoint(ray, tempIntersection.distance);
    }
    else
      tempIntersection.isValid = false;
  }

  return tempIntersection;
}

Sphere::Sphere(Vector3D pos_, float radius_, Material inMaterial)
{
  radius = radius_;
  pos = pos_;
  mat = inMaterial;
}
