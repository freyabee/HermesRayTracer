#include "RayTracer.h"



RayTracer::RayTracer()
{
}


RayTracer::~RayTracer()
{
}

glm::vec3 RayTracer::TraceRay(Ray _ray)
{
	glm::vec3 pix = glm::vec3(1.0, 0.0, 0.0);

	return pix;
}

glm::vec3 RayTracer::ClosestPoint(Ray _ray, glm::vec3 _point)
{
	glm::vec3 temp = dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}

Collision RayTracer::SphereIntersection(Ray _ray, glm::vec3 _centre, int _radius)
{
	glm::vec3 pX = ClosestPoint(_ray, _centre);

	dot((_centre - _ray.origin),_ray.direction).
	return Collision();
}

float RayTracer::dot(glm::vec3 _v1, glm::vec3 _v2)
{
	return (_v1.x*_v2.x) + (_v1.y*_v2.y) + (_v1.z*_v2.z);
}

float RayTracer::pythag(float _radius, float _distance)
{
	return sqrt((pow(_radius, 2) - pow(_distance, 2)));
}

float RayTracer::vec3dist(glm::vec3 p1, glm::vec3 p2)
{
	return 0.0f;
}
