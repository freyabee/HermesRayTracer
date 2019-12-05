#include "Light.h"


Light::Light()
{
}


Light::~Light()
{
}

glm::vec3 Light::ShadePixel(Ray _ray, Collision _col)
{

	return glm::vec3(1.0f, 1.0f, 1.0f);
}



void Light::SetCentre(glm::vec3 _centre)
{
	centre = _centre;
}

void Light::SetRadius(float _radius)
{
	radius = _radius;
}

glm::vec3 Light::GetCentre()
{
	return centre;
}

float Light::GetRadius()
{
	return radius;
}
