#ifndef Intersection_h__
#define Intersection_h__

#include "Ray.h"

class Object;
struct Ray;
struct Vector3D;

struct Intersection {

  Intersection();

  void setIntersectionPoint(Ray inRay, float t);

  bool isValid;
  float distance;
  Vector3D interSectionPoint;
  Vector3D intersectionNormal;
  Ray intersectionRay;

  int intersectingObjID;
  Object* intersectingObject;   //Use only when primitive objects are used
  int intersectingMatID;
};

#endif // Intersection_h__
