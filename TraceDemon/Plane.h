#ifndef Plane_h__
#define Plane_h__

#include "Object.h"

struct Intersection;

struct Plane : public Object
{
	Vector3D normal;

	Plane(Vector3D inPos, Vector3D  inNormal, Material inMaterial);

	virtual Vector3D getNormal(Intersection);

	virtual Intersection getIntersection(Ray inRay);

};

#endif // Plane_h__