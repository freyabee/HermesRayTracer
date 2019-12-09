#pragma once
#include "MCG_GFX_Lib.h"
#include <memory>

class Ray;
class Collision;
class DirectionalLight;
class Material;

class Object
{
public:
	Object();
	~Object();
	virtual Collision Intersection(Ray _ray) = 0;
	virtual Collision SIntersection(Ray _ray) = 0;
	virtual glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> _light, bool _inShadow) = 0;
	virtual glm::vec3 ReturnSurfaceNormal(Collision _col) = 0;
	virtual glm::vec3 NormalShader(Ray _ray, Collision _col) = 0;
	virtual glm::vec3 DebugShader() = 0;

	glm::vec3 Object::ClosestPoint(Ray _ray, glm::vec3 _point);

	//getter
	virtual std::shared_ptr<Material> GetMaterial() = 0;
	//setter
	
	//Getters
	virtual glm::vec3 GetCentre() = 0;
}; 

