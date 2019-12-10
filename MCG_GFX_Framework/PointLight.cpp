#include "PointLight.h"
#include <vector>


PointLight::PointLight()
{

}
PointLight::PointLight(glm::vec3 _centre, float _intensity, glm::vec3 _color)
{
	intensity = _intensity;
	centre = _centre;
	color = _color;
}

PointLight::PointLight(glm::vec3 _centre, float _intensity, float _radius, glm::vec3 _color)
{
	intensity = _intensity;
	centre = _centre;
	radius = _radius;
	color = _color;
}

PointLight::~PointLight()
{
}




glm::vec3 PointLight::CalculateShadingInfo(glm::vec3 _hitPoint)
{

	glm::vec3 lightDir = lightDir = centre - _hitPoint;
	float distance = glm::length(lightDir);
	lightDir = glm::normalize(lightDir);
	glm::vec3 lightIntensity = intensity * color / (4 * glm::pi<float>() * distance);

	return lightIntensity;
}

glm::vec3 PointLight::GetDirection(glm::vec3 _hitPoint)
{
	//Retur
	glm::vec3 lightDir = glm::normalize(lightDir = centre - _hitPoint);
	return lightDir;
}

float PointLight::GetIntensity()
{
	return intensity;
}

glm::vec3 PointLight::GetCentre()
{
	return centre;
}

glm::vec3 PointLight::GetColor()
{
	return color;
}

float PointLight::GetRadius()
{
	return radius;
}
