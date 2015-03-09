#ifndef MathFunctions_h__
#define MathFunctions_h__

#define _USE_MATH_DEFINES
#include <math.h>

float AngleToRadian(float angle){
	return ((angle * M_PI) / 180.0f);
}

#endif // MathFunctions_h__