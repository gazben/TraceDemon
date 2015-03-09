#include "Intersection.h"
#include "Object.h"

void Intersection::setIntersectionPoint(Ray inRay, float t)
{
  intersectionRay = inRay;
  intersectionRay.directionVec = intersectionRay.directionVec.getNormalized();
  interSectionPoint = inRay.startPos + (t*inRay.directionVec);
}

Intersection::Intersection()
{
  isValid = false;
  distance = 0;
  intersectingObjID = 0;
  intersectingMatID = 0;

  intersectingObject = nullptr;
}
