#pragma once
#include "Sphere.h"

class Light : public Sphere
{
public:
	Light();
	~Light();
	glm::vec3 Light::ShadePixel(Ray _ray, Collision _col);
	void SetCentre(glm::vec3 _centre);
	void SetRadius(float _radius);
	glm::vec3 GetCentre();
	float GetRadius();
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;


};

