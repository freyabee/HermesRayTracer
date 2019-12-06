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
private:
	glm::vec3 pixelColour;
	glm::vec3 centre;
	float radius;
	std::shared_ptr<Material> material;
public:
	Sphere();
	 ~Sphere();
	 
	glm::vec3 ShadePixel(Ray _ray, Collision _col);
	glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight>);
	
	Collision Intersection(Ray _ray);
	
	//Getters
	glm::vec3 GetCentre();
	float GetRadius();
	std::shared_ptr<Material> GetMaterial();
	 //Setters
	void SetCentre(glm::vec3 _centre);
	void SetRadius(float _radius);
	void SetMaterial(std::shared_ptr<Material>);
	

};

