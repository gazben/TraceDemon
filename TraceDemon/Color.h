#ifndef Color_h__
#define Color_h__

struct Color {
  float r, g, b;

  Color() {
    r = g = b = 0;
  }
  Color(float r0, float g0, float b0) {
    r = r0; g = g0; b = b0;
  }
  Color(float _color[3]){
    r = _color[0];
    g = _color[1];
    b = _color[2];
  }
  Color operator*(float a) {
    return Color(r * a, g * a, b * a);
  }
  Color operator*(const Color& c) {
    return Color(r * c.r, g * c.g, b * c.b);
  }
  Color operator/(const Color& c) {
    return Color(r / c.r, g / c.g, b / c.b);
  }
  Color operator+(const Color& c) {
    return Color(r + c.r, g + c.g, b + c.b);
  }
  Color operator-(const Color& c) {
    return Color(r - c.r, g - c.g, b - c.b);
  }

  float getNorm_B(){
    return b / 255.0f;
  }

  float getNorm_G(){
    return g / 255.0f;
  }

  float getNorm_R(){
    return r / 255.0f;
  }
};

namespace Colors{
  extern Color red;
  extern Color grey;
  extern Color blue;
  extern Color green;
  extern Color purple;
  extern Color white;
}

#endif // Color_h__