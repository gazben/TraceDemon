#ifndef Ray_h__
#define Ray_h__

#include "Vector3D.h"

struct Ray
{
	Vector3D startPos;
	Vector3D directionVec;

	Ray(){}

	Ray(Vector3D inStartPos, Vector3D inDirectionVec){
		this->directionVec = inDirectionVec.getNormalized();
		this->startPos = inStartPos;
	}
};

#endif // Ray_h__