#include <iostream>
#include <fstream>

#include <thread>
#include <mutex>
#ifdef _DEBUG
#include <stdio.h>
#endif // DEBUG

#include "Scene.h"
#include "Light.h"
#include "Intersection.h"
#include "Object.h"
#include "Material.h"
#include "Triangle.h"

Color Scene::getIntersectColor(Ray inRay)
{
  Intersection tempIntersect;
  Color color = Color(0.0f, 0.0f, 0.0f);
  Color reflectedColor(1.0, 1.0, 1.0);
  Color refractedColor(1.0, 1.0, 1.0);

  Color KA = Materials::MaxDefault.AmbientColor();//materials[0].ambient;
  Color KD = Materials::MaxDefault.DiffuseColor();//materials[0].diffuse;
  Color KS = Materials::MaxDefault.SpecularColor();//materials[0].specular;
  float SpecularLevel = Materials::MaxDefault.SpecularLevel();//materials[0].shininess;

  tempIntersect = getClosestIntersection(inRay);

  if (!tempIntersect.isValid) {
    return Color(0.0f, 0.0f, 0.0f);
  }

  for (int i = 0; i < lights.size(); i++) {
    Vector3D lightVector = lights[i].pos - tempIntersect.interSectionPoint;

    float intensity = pow(1.0 / (lightVector.Length()), 2);

    Vector3D V = tempIntersect.intersectionRay.directionVec * -1;
    Vector3D L = (lights[i].pos - tempIntersect.interSectionPoint).getNormalized();
    Vector3D H = (V + L).getNormalized();
    Vector3D N = tempIntersect.intersectionNormal;

    float lnScalar = L * N;
    lnScalar = lnScalar;
    if (lnScalar < EPSILON) {
      lnScalar = 0.0f;
    }

    float hnScalar = H * N;
    if (hnScalar < EPSILON) {
      hnScalar = 0.0f;
    }

    /*
    Color KD = tempIntersect.intersectingObject->Mat().DiffuseColor();
    Color KS = tempIntersect.intersectingObject->Mat().SpecularColor();
    int SHINE = tempIntersect.intersectingObject->Mat().SpecularLevel();
    */

    Color cDiffuse = KD*lnScalar;
    Color cSpecular = KS*powf(hnScalar, SpecularLevel);
    color = color + ((lights[i].lightColor) * (cDiffuse + cSpecular)) * intensity;
  }

  return color + KA;
}

Intersection Scene::getClosestIntersection(Ray inRay)
{
  Intersection closestIntersect;

  Vector3D a;
  Vector3D b;
  Vector3D c;

  Triangle currentTriangle;
  //Get the triangles
  if (!shapes.empty()){

    for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.indices.size(); v = v + 3) {

        a = Vector3D(
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v] * 3 + 0) ],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v] * 3 + 1) ],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v] * 3 + 2) ]
          );
        b = Vector3D(
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 1] * 3 + 0)],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 1] * 3 + 1)],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 1] * 3 + 2)]
          );
        c = Vector3D(
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 2] * 3 + 0)],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 2] * 3 + 1)],
          shapes[i].mesh.positions[(shapes[i].mesh.indices[v + 2] * 3 + 2)]
          );
        
        Vector3D n = Vector3D(
          shapes[i].mesh.normals[(shapes[i].mesh.indices[v] * 3 + 0)],
          shapes[i].mesh.normals[(shapes[i].mesh.indices[v] * 3 + 1)],
          shapes[i].mesh.normals[(shapes[i].mesh.indices[v] * 3 + 2)]
          );

        currentTriangle = Triangle(a, b, c, n);
        Intersection tempIntersect;
        tempIntersect = currentTriangle.getIntersection(inRay);

        if (((tempIntersect.distance < closestIntersect.distance) && tempIntersect.isValid) || (!closestIntersect.isValid && tempIntersect.isValid))
          closestIntersect = tempIntersect;
      }
    }
  }

  return closestIntersect;
}

void Scene::Draw(int x, int y)
{
  Ray tempRay = camera.getRay(x, y);
  Color pixelcolor = getIntersectColor(tempRay);

  image[y][x] = pixelcolor;
}

Scene::~Scene()
{
}

Scene::Scene()
{
}

void Scene::LoadObj(std::string ObjFilePath, std::string MaterialFilePath)
{
  lights.push_back(Light(Vector3D(1, 3, 2.73), Colors::white));

  std::string err = tinyobj::LoadObj(shapes, materials, ObjFilePath.c_str(), MaterialFilePath.c_str());

  if (!err.empty())
  {
    std::cerr << err << std::endl;
    getchar();
    exit(1);
  }

#ifdef _DEBUG
  std::cout << " -- OBJ loader file loading info -- " << std::endl;
  std::cout << "# of shapes : " << shapes.size() << std::endl;

  for (size_t i = 0; i < shapes.size(); i++) {
    printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
    printf("shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());

    for (size_t f = 0; f < shapes[i].mesh.indices.size(); f++) {
      printf("  idx[%ld] = %d\n", f, shapes[i].mesh.indices[f]);
    }

    printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());

    for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
      printf("  v[%ld] = (%f, %f, %f)\n", v,
        shapes[i].mesh.positions[3 * v + 0],
        shapes[i].mesh.positions[3 * v + 1],
        shapes[i].mesh.positions[3 * v + 2]);
    }
    printf("\n");
  }
#endif // DEBUG

}

Intersection Scene::RayIntersectTriangle(Vector3D p0, Vector3D p1, Vector3D p2, Ray r)
{
  return Intersection();
}

bool Scene::isRayCollidesWithTriangle(Vector3D p0, Vector3D p1, Vector3D p2, Ray r)
{
  return false;
}