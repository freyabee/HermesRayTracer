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

	pixelColour = glm::vec3(1.0, 0.0, 0.0);
	return pixelColour;
}

void Sphere::SetCentre(glm::vec3 _centre)
{
	centre = _centre;
}

void Sphere::SetRadius(float _radius)
{
	radius = _radius;
}

glm::vec3 Sphere::GetCentre()
{
	return centre;
}

float Sphere::GetRadius()
{
	return radius;
}
