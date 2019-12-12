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
class PointLight;
class Scene;

class RayTracer
{
private:
	float bias = 1e-4f;
	glm::vec3 backgroundColor;



public:
	RayTracer();
	RayTracer(glm::vec3 _backgroundColor);
	~RayTracer();
	// Traces a ray and returns a color.
	glm::vec3 TraceRay(Ray _ray, int depth = 0);
	// Gets closest point on a line
	glm::vec3 ClosestPoint(Ray _ray, glm::vec3 _point);
	bool CalculateShadows(Collision _col);
	glm::vec3 CalculatePointLights(Collision _col);
	std::vector<Collision> GetCollisions(Ray _ray);
	Collision GetClosestCollision(std::vector<Collision> _collisions);
	Ray GetReflectionRay(Ray _ray, Collision _col);

	//gets reflection vector of point given the ray and surface normal
	glm::vec3 Reflection(glm::vec3 _rayDir, glm::vec3 _surfaceNormal);


	std::vector<std::shared_ptr<Object>> objectArray;
	std::vector<std::shared_ptr<DirectionalLight>> dlArray;
	std::vector<std::shared_ptr<Plane>> planeArray;
	std::vector < std::shared_ptr<PointLight>> plArray;
	
	void AddScene(Scene scene);

	void AddSphereToScene(glm::vec3 _coordinate, float _radius, std::shared_ptr<Material>);
	void AddDirectionalLightToScene(glm::vec3 _coordinate, glm::vec3 _direction, float intensity);
	void AddPlaneToScene(glm::vec3 _coordinate, glm::vec3 _normal, std::shared_ptr<Material> _material);
	void AddPointLightToScene(glm::vec3 _centre, float _intensity, glm::vec3 _color);
};

