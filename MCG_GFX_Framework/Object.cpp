#include "Object.h"
#include "Ray.h"
#include "Collision.h"
#include "DirectionalLight.h"
#include "Material.h"

Object::Object()
{
}


Object::~Object()
{
}

Collision Object::Intersection(Ray _ray)
{
	return Collision();
}


glm::vec3 Object::DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> light, glm::vec3 _plVec, bool inShadow)
{
	return glm::vec3();
}

glm::vec3 Object::ClosestPoint(Ray _ray, glm::vec3 _point)
{
	glm::vec3 temp = glm::dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}