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
	glm::vec3 temp = glm::dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}

Collision RayTracer::SphereIntersection(Ray _ray, glm::vec3 _centre, int _radius)
{
	Collision sphereCol;
	bool isCollided = false;

	//Check if ray origin is inside sphere
	float radiusCheck = vec3dist(_ray.origin, _centre);
	if (radiusCheck <= _radius)
	{
		isCollided = false;
		std::cout << "ERROR: Ray origin within circle" << std::endl;
		return sphereCol;
	}
	//Find closest point on ray to centre of sphere
	glm::vec3 closestPoint = ClosestPoint(_ray, _centre);

	//Check if closes point is in front or behind the ray origin/direction - point - ray origin
	if (glm::length(closestPoint - _ray.origin)<0)
	{
		std::cout << "ERROR: shape behind ray" << std::endl;
		sphereCol.setCollided(false);
		return sphereCol;
	}


	//Work out distance from closes point to sphere centre (D)

	//vector between centre point and closest point.
	glm::vec3 dVec = _centre - _ray.origin - (dot((_centre - _ray.origin), _ray.direction)*_ray.direction);
	//length of vector between centre and closest point X )
	float d = sqrt((dVec.x*dVec.x) + (dVec.y*dVec.y) + (dVec.z*dVec.z));

	//distance between collision point and closest point
	float x = sqrt((_radius*_radius) - (d*d));

	//first point of intersection (3d vec) 
	glm::vec3 col = _ray.origin*(((dot((_centre - _ray.origin), _ray.direction)) - x)*_ray.direction);

	float collisionDist = glm::length(col - _ray.origin);
	sphereCol.setCollided(true);
	sphereCol.setCollisionPoint(col);
	sphereCol.setCollisionDistance(collisionDist);
	return sphereCol;
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
	return glm::length(p1 - p2);
}
