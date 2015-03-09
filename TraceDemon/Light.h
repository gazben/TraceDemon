#ifndef Light_h__
#define Light_h__

#include "Color.h"
#include "Vector3D.h"

struct Light
{
	Vector3D pos;
	Color lightColor;

	Light(Vector3D inPos, Color inColor){
		pos = inPos;
		lightColor = inColor;
	}
};

#endif // Light_h__