#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
class RayTracer
{
public:
	RayTracer();
	~RayTracer();
	glm::vec3 TraceRay(Ray _ray);
};

