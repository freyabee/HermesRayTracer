#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

glm::vec3 Sphere::ShadePixel(Ray _ray, Collision _col)
{
	/*
	TODO: Function that shades pixel and returns pixel color in vec3
	*/

	glm::vec3 surfaceNormal = (_col.GetCollisionPoint() - centre) * (1.0f/radius);

	glm::vec3 normdir= (-_ray.direction);


	float hitColor = glm::max(glm::dot(surfaceNormal, normdir),0.0f);
	//std::cout << hitColor << std::endl;
	pixelColour = glm::vec3(0.9f, 0.0, 0.0);

	glm::vec3 color = pixelColour * (hitColor);

	return (color);
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
