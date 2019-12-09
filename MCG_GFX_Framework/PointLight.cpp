#include "PointLight.h"



PointLight::PointLight()
{
}


PointLight::PointLight(glm::vec3 _centre, float _intensity)
{
	intensity = _intensity;
	centre = _centre;
}

PointLight::~PointLight()
{
}

void PointLight::CalculateShadingInfo(glm::vec3 _hitPoint, std::unique_ptr<glm::vec3> _lightDir, std::unique_ptr<glm::vec3> _lightIntensity)
{

	glm::vec3 lightDirection = centre - _hitPoint;

	float r2 = glm::length(lightDirection);

}
