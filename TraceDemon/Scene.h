#ifndef Scene_h__
#define Scene_h__

#include <vector>
#include <string>

#include "Config.h"
#include "Intersection.h"
#include "Color.h"
#include "Camera.h"
#include "Light.h"
#include "Vector3D.h"

#include "Loader/tiny_obj_loader.h"


class Scene{
public:
	Scene();
	~Scene();

	void Draw(int , int);
	Intersection getClosestIntersection(Ray inRay);
	void LoadObj(std::string ObjFilePath, std::string MaterialFilePath);

	Color getIntersectColor( Ray inRay );

	Color image[SCREENHEIGHT][SCREENWIDTH];

private:
	Camera camera;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
  
	std::vector<Light> lights;

  //Private functions:
  Intersection RayIntersectTriangle(Vector3D p0 , Vector3D p1 , Vector3D p2 , Ray r);
  bool isRayCollidesWithTriangle(Vector3D p0, Vector3D p1, Vector3D p2, Ray r);

};

#endif // Scene_h__