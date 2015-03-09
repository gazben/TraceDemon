#ifndef Material_h__
#define Material_h__

#include <math.h>

#include "Color.h"

class Material
{
public:
	Material();

	Material(
		Color inDiffuseColor,
		Color inSpecularColor,
		Color inAmbientColor,

		Color inN,
		Color inK,
		float inSpecularLevel,

		bool inSsReflective,
		bool inIsRefractive
		);

	Color Fresnel(float cosAlfa);
	Color DiffuseColor();
	Color SpecularColor();
	Color AmbientColor();
	float SpecularLevel() ;
	Color N();
	Color K();
	bool IsReflective();
	bool IsRefractive();

protected:

	Color diffuseColor;
	Color specularColor;
	Color ambientColor;
	Color n;
	Color k;
	float specularLevel;
	bool isReflective;
	bool isRefractive;
};

namespace Materials{
	extern Material silver;
	extern Material gold;
	extern Material diffuseGreen;
	extern Material glass;
  extern Material MaxDefault;
}

#endif // Material_h__