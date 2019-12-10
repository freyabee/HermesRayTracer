#include "PointLight.h"
#include "Material.h"
#include <vector>
#include "Collision.h"


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




glm::vec3 PointLight::CalculateShadingInfo(Collision _hitcol)
{

	glm::vec3 lightDir = centre - _hitcol.GetCollisionPoint();
	float r2 = glm::length(lightDir);
	glm::vec3 lightIntensity = intensity * color / (4 * glm::pi<float>() * r2);

	//lightIntensity *= _hitcol.GetHitObject()->GetMaterial()->GetAlbedo();
	lightIntensity *= std::max(0.f, glm::dot(_hitcol.GetCollisionNormal(), glm::normalize(lightDir)));
	return glm::clamp(lightIntensity, 0.f, 1.0f);
	//return lightIntensity;
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
