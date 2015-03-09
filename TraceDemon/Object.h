#ifndef Object_h__
#define Object_h__

#include "Material.h"
#include "Vector3D.h"

struct Ray;
struct Intersection;

class Object{
public:
	Material Mat() { return mat; }
	void Mat(Material val) { mat = val; }

	virtual Intersection getIntersection(Ray) = 0;
	virtual Vector3D getNormal(Intersection) = 0;

protected:
	Vector3D pos;
	Material mat;

};

#endif // Object_h__