#pragma once
#include "Light.h"

class Collision;

class PointLight
{
public:
	PointLight();
	PointLight(glm::vec3 _centre, float _intensity, glm::vec3 _color);
	PointLight(glm::vec3 _centre, float _intensity, float radius, glm::vec3 _color);
	~PointLight();
	glm::vec3 CalculateShadingInfo(Collision _hitCol);
	glm::vec3 GetDirection(glm::vec3 _hitPoint);
	float GetIntensity();
	glm::vec3 GetCentre();
	glm::vec3 GetColor();
	float GetRadius();

private:
	glm::vec3 centre;
	glm::vec3 color;
	float intensity;
	float radius;

};

