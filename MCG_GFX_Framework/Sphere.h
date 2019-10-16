#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
class Sphere
{
private:
	glm::vec3 pixelColour;
public:
	Sphere();
	~Sphere();
	glm::vec3 ShadePixel(Ray _ray);
};

