#ifndef Sphere_h__
#define Sphere_h__

#include <math.h>

#include "Object.h"

struct Sphere :public Object
{
	float radius;

	Sphere(Vector3D pos_, float radius_, Material inMaterial);

	Intersection getIntersection(Ray ray);

	virtual Vector3D getNormal(Intersection intersection);
};

#endif // Sphere_h__