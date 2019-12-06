#pragma once
#include "MCG_GFX_Lib.h"
#include <memory>

class Ray;
class Collision;
class DirectionalLight;


class Object
{
public:
	Object();
	~Object();
	virtual Collision Intersection(Ray _ray) = 0;
	virtual glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> light) = 0;
	glm::vec3 Object::ClosestPoint(Ray _ray, glm::vec3 _point);
}; 

