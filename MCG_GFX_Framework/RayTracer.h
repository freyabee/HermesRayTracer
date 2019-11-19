#pragma once
#include <memory>
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
	std::vector<Sphere> objectArray;

	void AddSphereToScene(glm::vec3 _coordinate, float _radius);
	void AddLightToScene(glm::vec3 _coordinate, float _radius);

};

