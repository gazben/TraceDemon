#ifndef Camera_h__
#define Camera_h__

#include "Config.h"
#include "Vector3D.h"

class Ray;

class Camera{

public:
	Camera();

	Ray getRay(int x, int y);

private:

	Vector3D CameraPos;
	Vector3D TargetPos;

	Vector3D PixelHeight_Width;

	Vector3D CameraDirVec;
	Vector3D CameraDirVec_Horizontal;
	Vector3D CameraDirVec_Vertical;

	Vector3D CameraUp;

	float aspectRatio;
	float fov;
};

#endif // Camera_h__