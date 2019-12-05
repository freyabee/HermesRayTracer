#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Collision.h"
#include <algorithm>
#include <iostream>
#include "Object.h"

class Sphere
{
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;
public:
	Sphere();
	virtual ~Sphere();
	virtual glm::vec3 ShadePixel(Ray _ray, Collision _col);
	virtual void SetCentre(glm::vec3 _centre);
	virtual void SetRadius(float _radius);
	virtual glm::vec3 GetCentre();
	virtual float GetRadius();
};

