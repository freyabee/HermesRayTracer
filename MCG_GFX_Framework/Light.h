#pragma once
#include "Sphere.h"

class Light
{
public:
	Light();
	~Light();

	virtual void SetIntensity(float _intensity) = 0; 
	virtual void SetDirection(glm::vec3 _direction) = 0;

	virtual float GetIntensity() = 0;
	virtual glm::vec3 GetDirection() = 0;
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;


};

