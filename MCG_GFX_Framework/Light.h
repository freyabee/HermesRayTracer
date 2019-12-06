#pragma once
#include "Sphere.h"

class Light
{
public:
	Light();
	~Light();
	virtual glm::vec3 Light::ShadePixel(Ray _ray, Collision _col);
	void SetCentre(glm::vec3 _centre);
	void SetRadius(float _radius);
	glm::vec3 GetCentre();
	float GetRadius();

	virtual void SetIntensity(float _intensity);
	virtual void SetDirection(glm::vec3 _direction);
	virtual void SetCoordinate(glm::vec3 _coordinate);

	virtual float GetIntensity();
	virtual glm::vec3 GetDirection();
	virtual	glm::vec3 GetCoordinate();
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;


};

