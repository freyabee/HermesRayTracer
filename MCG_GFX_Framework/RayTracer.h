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
class Camera;


class RayTracer
{
private:
	float bias = 1e-4f;
public:
	RayTracer();
	~RayTracer();
	// Traces a ray and returns a color.
	glm::vec3 TraceRay(Ray _ray, int depth = 0);
	// Gets closest point on a line
	glm::vec3 ClosestPoint(Ray _ray, glm::vec3 _point);
	Collision GetShadows(int element, Collision _col, std::shared_ptr<Object> obj);
	//gets reflection vector of point given the ray and surface normal
	glm::vec3 Reflection(glm::vec3 _rayDir, glm::vec3 _surfaceNormal);


	std::vector<std::shared_ptr<Object>> objectArray;
	std::vector<std::shared_ptr<DirectionalLight>> dlArray;
	std::vector<std::shared_ptr<Plane>> planeArray;
	
	void AddSphereToScene(glm::vec3 _coordinate, float _radius, std::shared_ptr<Material>);
	void AddDirectionalLightToScene(glm::vec3 _coordinate, glm::vec3 _direction, float intensity);
	void AddPlaneToScene(glm::vec3 _coordinate, glm::vec3 _normal, std::shared_ptr<Material> _material);
};

