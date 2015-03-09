#ifndef Triangle_h__
#define Triangle_h__

#include "Vector3D.h"
#include "Object.h"
#include "Intersection.h"

struct Triangle :Object
{
  Vector3D a;
  Vector3D b;
  Vector3D c;
  Vector3D normal;

  Triangle(){
  }

  Triangle(Vector3D inA, Vector3D inB, Vector3D inC, Vector3D normal_ = Vector3D() ){
    a = inA;
    b = inB;
    c = inC;
    normal = normal_;
  }

  void setPosition(Vector3D inA, Vector3D inB, Vector3D inC, Vector3D normal_ = Vector3D()){
    a = inA;
    b = inB;
    c = inC;
    normal = normal_;
  }

  virtual Intersection getIntersection( Ray ray ){
    Intersection tempIntersection;

    Vector3D e1, e2;  //Edge1, Edge2
    Vector3D P, Q, T;
    float det, inv_det, u, v;
    float t;

    //Find vectors for two edges sharing V1
    e1 = b - a;
    e2 = c - a;
    //Begin calculating determinant - also used to calculate u parameter
    P = Vector3D::CrossProduct(ray.directionVec, e2);
    //if determinant is near zero, ray lies in plane of triangle
    det = Vector3D::DotProduct(e1, P);
    //NOT CULLING
    if (det > -EPSILON && det < EPSILON){
      tempIntersection.isValid = false;
      return tempIntersection;
    }

    inv_det = 1.f / det;

    //calculate distance from V1 to ray origin
    T = ray.startPos - a;

    //Calculate u parameter and test bound
    u = Vector3D::DotProduct(T, P) * inv_det;
    //The intersection lies outside of the triangle
    if (u < 0.f || u > 1.f){
      tempIntersection.isValid = false;
      return tempIntersection;
    }

    //Prepare to test v parameter
    Q = Vector3D::CrossProduct(T, e1);

    //Calculate V parameter and test bound
    v = Vector3D::DotProduct(ray.directionVec , Q) * inv_det;
    //The intersection lies outside of the triangle
    if (v < 0.f || u + v  > 1.f){
      tempIntersection.isValid = false;
      return tempIntersection;
    }

    t = Vector3D::DotProduct(e2, Q) * inv_det;

    if (t > EPSILON) {
      tempIntersection.isValid = true;
      tempIntersection.setIntersectionPoint(ray, t);
      tempIntersection.intersectionRay = ray;
      tempIntersection.distance = t;
      tempIntersection.intersectionNormal = normal;
      return tempIntersection;
    }

    tempIntersection.isValid = false;
    return tempIntersection;
  }

  virtual void setMaterial(Material inMaterial)
  {
    mat = inMaterial;
  }

  virtual Vector3D getNormal(Intersection intersection)
  {
    return normal;
  }
};
#endif // Triangle_h__