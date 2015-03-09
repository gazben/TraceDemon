#include "Camera.h"

#include "Ray.h"
#include "MathFunctions.h"
#include "Config.h"

Ray Camera::getRay(int x, int y)
{
	Ray tempRay(

		this->CameraPos,
		CameraDirVec +
		(CameraDirVec_Horizontal *
		(x - SCREENWIDTH / 2.0) *
		PixelHeight_Width.x
		+ CameraDirVec_Vertical *
		(SCREENHEIGHT / 2.0 - y) *
		PixelHeight_Width.y)
		);

	tempRay.directionVec = tempRay.directionVec.getNormalized();

	return tempRay;
}

Camera::Camera()
{
	aspectRatio = SCREENWIDTH / SCREENHEIGHT;

	fov = FOV;

	TargetPos = Vector3D(0, 0, 0);
	CameraPos = Vector3D(3, 3, 3);

	CameraUp = Vector3D(0, 0, -1).getNormalized();

	CameraDirVec = (TargetPos - CameraPos).getNormalized();

	CameraDirVec_Horizontal = (CameraDirVec % CameraUp).getNormalized();

	CameraDirVec_Vertical = (CameraDirVec_Horizontal % CameraDirVec).getNormalized();

	PixelHeight_Width.y = (2 * tan(AngleToRadian(fov / 2.0))) / SCREENHEIGHT;
	PixelHeight_Width.x = (2 * aspectRatio * tan(AngleToRadian(fov / 2.0))) / SCREENWIDTH;
}
