#include "Light.h"
#include "Collision.h"
#include "Ray.h"

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

void Light::SetIntensity(float _intensity)
{
}

void Light::SetDirection(glm::vec3 _direction)
{
}

void Light::SetCoordinate(glm::vec3 _coordinate)
{
}

float Light::GetIntensity()
{
	return 0.0f;
}

glm::vec3 Light::GetDirection()
{
	return glm::vec3();
}

glm::vec3 Light::GetCoordinate()
{
	return glm::vec3();
}
