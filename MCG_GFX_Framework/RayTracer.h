#pragma once
#include <memory>
#include "MCG_GFX_Lib.h"
#include <iostream>
#include <vector>

class Sphere;
class Collision;
class DirectionalLight;
class Ray;
class Plane;
class Material;
class Object;

class RayTracer
{
private:

public:

	RayTracer();
	~RayTracer();
	// Traces a ray and returns a color.
	glm::vec3 TraceRay(Ray _ray);
	// Gets closest point on a line
	glm::vec3 ClosestPoint(Ray _ray, glm::vec3 _point);
	Collision SphereIntersection(Ray _ray, glm::vec3 _centre, float _radius);


	std::vector<std::shared_ptr<Object>> objectArray;
	std::vector<std::shared_ptr<DirectionalLight>> dlArray;
	std::vector<std::shared_ptr<Plane>> planeArray;
	
	void AddSphereToScene(glm::vec3 _coordinate, float _radius, std::shared_ptr<Material>);
	void AddLightToScene(glm::vec3 _coordinate, float _radius);
	void AddDirectionalLightToScene(glm::vec3 _coordinate, glm::vec3 _direction, float intensity);
	void AddPlaneToScene(glm::vec3 _coordinate, glm::vec3 _normal);
};

