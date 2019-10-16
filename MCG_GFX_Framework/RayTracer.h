#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
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


};

