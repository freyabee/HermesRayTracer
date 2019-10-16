#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

glm::vec3 Sphere::ShadePixel(Ray _ray)
{
	/*
	Function that shades pixel and returns pixel color in vec3
	*/

	pixelColour = glm::vec3(1, 0, 0);
	return pixelColour;
}
