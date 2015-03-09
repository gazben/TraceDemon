#include "Material.h"

Color Material::Fresnel(float cosAlfa)
{
	Color white(1, 1, 1);
	Color fresnel0 = ((n - white)*(n - white) + (k*k)) / ((n + white)*(n + white) + (k*k));
	Color tempFresnel = fresnel0 + (white - fresnel0)*powf(1 - cosAlfa, 5);

	return tempFresnel;
}

Material::Material(Color inDiffuseColor, Color inSpecularColor, Color inAmbientColor, Color inN, Color inK, float inSpecularLevel, bool inSsReflective, bool inIsRefractive)
{
	diffuseColor = inDiffuseColor;
	specularColor = inSpecularColor;
	ambientColor = inAmbientColor;

	n = inN;
	k = inK;
	specularLevel = inSpecularLevel;

	isReflective = inSsReflective;
	isRefractive = inIsRefractive;
}

Material::Material()
{
}

Color Material::AmbientColor() 
{
	return ambientColor;
}

Color Material::SpecularColor() 
{
	return specularColor;
}

Color Material::DiffuseColor() 
{
	return diffuseColor;
}

bool Material::IsRefractive() 
{
	return isRefractive;
}

bool Material::IsReflective() 
{
	return isReflective;
}

Color Material::K() 
{
	return k;
}

Color Material::N() 
{
	return n;
}

float Material::SpecularLevel() 
{
	return specularLevel;
}

namespace Materials{
	Material silver(Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.14, 0.16, 0.13), Color(4.1, 2.3, 3.1), 0, true, false);
	Material gold(Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.17, 0.35, 1.5), Color(3.1, 2.7, 1.9), 0, true, false);
	Material diffuseGreen(Color(0.1, 0.4, 0.05), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), 0, false, false);
	Material glass(Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Color(1.5, 1.5, 1.5), Color(0, 0, 0), 0, true, true);
  Material MaxDefault(Color(0.3451, 0.5647, 0.8824), Color(0.3451, 0.5647, 0.8824), Color(0.35, 0.35, 0.35 ), Color(1.5, 1.5, 1.5), Color(0, 0, 0), 0, false, false);

}
