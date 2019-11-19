#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Collision.h"
#include <algorithm>
#include <iostream>

class Sphere
{
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;
public:
	Sphere();
	~Sphere();
	glm::vec3 ShadePixel(Ray _ray, Collision _col);
	void SetCentre(glm::vec3 _centre);
	void SetRadius(float _radius);

	glm::vec3 GetCentre();
	float GetRadius();
};

