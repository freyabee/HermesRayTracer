#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Collision.h"
#include <iostream>
#include <vector>
#include "Sphere.h"
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
	float dot(glm::vec3 _v1, glm::vec3 _v2);
	float pythag(float _radius, float _distance);
	float vec3dist(glm::vec3 p1, glm::vec3 p2);
	std::vector<Sphere> objectArray;

	void AddSphereToScene(glm::vec3 _coordinate, float _radius);
};

