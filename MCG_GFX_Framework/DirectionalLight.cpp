#include "DirectionalLight.h"



DirectionalLight::DirectionalLight()
{
}


DirectionalLight::~DirectionalLight()
{
}

DirectionalLight::DirectionalLight(float _intensity, glm::vec3 _direction, glm::vec3 _color)
{
	intensity = _intensity;
	direction = glm::normalize(_direction);
	color = _color;
}

void DirectionalLight::SetIntensity(float _intensity)
{
	intensity = _intensity;
}

void DirectionalLight::SetDirection(glm::vec3 _direction)
{
	direction = _direction;
}

void DirectionalLight::SetColor(glm::vec3 _color)
{
	color = _color;
}

float DirectionalLight::GetIntensity()
{
	return intensity;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return glm::normalize(direction);
}

glm::vec3 DirectionalLight::GetColor()
{
	return color;
}
