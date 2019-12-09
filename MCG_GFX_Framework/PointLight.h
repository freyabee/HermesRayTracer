#pragma once
#include "Light.h"
class PointLight
{
public:
	PointLight();
	PointLight(glm::vec3 _centre, float _intensity);
	~PointLight();
	void CalculateShadingInfo(glm::vec3 _hitPoint, std::unique_ptr<glm::vec3> _lightDir, std::unique_ptr<glm::vec3> _lightIntensity);
private:
	glm::vec3 centre;
	float intensity;
};

