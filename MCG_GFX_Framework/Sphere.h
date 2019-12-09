#pragma once
#include "MCG_GFX_Lib.h"
#include <algorithm>
#include <iostream>
#include "Object.h"

class DirectionalLight;
class Material; 
class Collision;
class Ray;

class Sphere : public Object
{
public:
	Sphere();
	 ~Sphere();
	 //Shaders
	glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> _light, bool _inShadow);
	glm::vec3 NormalShader(Ray _ray, Collision _col);
	glm::vec3 DebugShader();
	//Collision
	Collision Intersection(Ray _ray);
	Collision SIntersection(Ray _ray);
	glm::vec3 ReturnSurfaceNormal(Collision _col);
	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	//Getters
	glm::vec3 GetCentre();
	float GetRadius();
	std::shared_ptr<Material> GetMaterial();
	 //Setters
	void SetCentre(glm::vec3 _centre);
	void SetRadius(float _radius);
	void SetMaterial(std::shared_ptr<Material>);

private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;
	std::shared_ptr<Material> material;
	

};

