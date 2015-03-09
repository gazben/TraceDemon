#ifndef Vector_h__
#define Vector_h__

#include <math.h>
#include "Config.h"

struct Vector3D {
  float x, y, z;

  Vector3D() {
    Init();
  }

  void Init(){
    x = y = z = 0;
  }

  Vector3D(float x0, float y0, float z0 = 0) {
    x = x0; y = y0; z = z0;
  }
  Vector3D operator*(float a) {
    return Vector3D(x * a, y * a, z * a);
  }
  Vector3D operator+(const Vector3D& v) {
    return Vector3D(x + v.x, y + v.y, z + v.z);
  }

  Vector3D operator/(float inFloat){
    this->x = this->x / inFloat;
    this->y = this->y / inFloat;
    this->z = this->z / inFloat;

    return *this;
  }

  bool operator==(Vector3D& inVector){
    if (this->x == inVector.x)
      if (this->y == inVector.y)
        if (this->z == inVector.z)
          return true;

    return false;
  }
  Vector3D operator-(const Vector3D& v) {
    return Vector3D(x - v.x, y - v.y, z - v.z);
  }
  float operator*(const Vector3D& v) {
    return (x * v.x + y * v.y + z * v.z);
  }
  Vector3D operator%(const Vector3D& v) {
    return Vector3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
  }
  float Length() {
    return sqrt(x * x + y * y + z * z);
  }

  void Normalize(){
    x = x / this->Length();
    y = y / this->Length();
    z = z / this->Length();
  }

  Vector3D getNormalized(){
    float length = Length();
    if (length < EPSILON) {
      length = EPSILON;
    }
    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
    return *this;
  }

  static Vector3D CrossProduct(Vector3D& v1, Vector3D& v2){
    return Vector3D(
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x
      );
  }

  static float DotProduct(Vector3D& v1, Vector3D& v2){
    return (
      v1.x * v2.x + 
      v1.y * v2.y + 
      v1.z * v2.z
      );
  }
};

inline Vector3D operator*(float inFloat, const Vector3D& inVector) {
  return Vector3D(inVector.x * inFloat, inVector.y * inFloat, inVector.z * inFloat);
}

#endif // Vector_h__
