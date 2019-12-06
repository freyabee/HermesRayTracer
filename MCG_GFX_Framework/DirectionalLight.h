#pragma once
#include "MCG_GFX_Lib.h"
#include "Light.h"


class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	DirectionalLight(float _intensity, glm::vec3 _direction, glm::vec3 _color);
	
	void SetIntensity(float _intensity);
	void SetDirection(glm::vec3 _direction);
	void SetCoordinate(glm::vec3 _coordinate);
	void SetColor(glm::vec3 _color);


	float GetIntensity();
	glm::vec3 GetDirection();
	glm::vec3 GetCoordinate();
	glm::vec3 GetColor();

private:
	glm::vec3 direction;
	float intensity;
	glm::vec3 coordinate;
	glm::vec3 color;

};

