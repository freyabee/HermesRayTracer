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
	//go through all objects in scene 

	Collision check;
	Sphere obj;
	float distHold = 999;
	bool col = false;
	for (std::vector<Sphere>::iterator it = std::begin(objectArray); it != std::end(objectArray); it++)
	{
		check = SphereIntersection(_ray, it->GetCentre(), it->GetRadius());


		if (check.GetCollided() == true)
		{

			//std::cout << "collided correctly" << std::endl;
			col = true;

			if (check.GetCollisionDist() < distHold)
			{
				distHold = check.GetCollisionDist();
				obj = *it;

				//std::cout << "smallest dist object found" << std::endl;
			}
		}
		else
		{
			//std::cout << "not collided" << std::endl;
		}
	}

	if (col == true)
	{

		return obj.ShadePixel(_ray);
	}
	else
	{
		//std::cout << "returning background color" << std::endl;
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

glm::vec3 RayTracer::ClosestPoint(Ray _ray, glm::vec3 _point)
{
	glm::vec3 temp = glm::dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}

Collision RayTracer::SphereIntersection(Ray _ray, glm::vec3 _centre, float _radius)
{
	Collision sphereCol;
	bool isCollided = false;



	//Check if ray origin is inside sphere
	if (glm::distance(_ray.origin, _centre) <= _radius)
	{
		isCollided = false;
		std::cout << "ERROR: Ray origin within circle" << std::endl;
		sphereCol.setCollided(false);
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
	glm::vec3 OriginToCentre = _centre - _ray.origin;

	glm::vec3 ClosestPointToCentre = (glm::dot(OriginToCentre, _ray.direction)*_ray.direction);

	glm::vec3 XToCentre = _centre - _ray.origin - ClosestPointToCentre;

	//length of vector between centre and closest point X )
	float d = glm::length(XToCentre);


	//std::cout << d << std::endl;
	if (d > _radius)
	{

		sphereCol.setCollided(false);
		return sphereCol;
	}
	else
	{
		//std::cout << "Collision found!" << std::endl;
	}

	//distance between collision point and closest point
	float x = sqrt((_radius*_radius) - (d*d));


	//first point of intersection (3d vec) 
	glm::vec3 col = _ray.origin*(((glm::dot((_centre - _ray.origin), _ray.direction)) - x)*_ray.direction);

	float collisionDist = glm::length(col - _ray.origin);
	sphereCol.setCollided(true);
	sphereCol.setCollisionPoint(col);
	sphereCol.setCollisionDistance(collisionDist);
	return sphereCol;
}
void RayTracer::AddSphereToScene(glm::vec3 _coordinate, float _radius)
{
	Sphere sphere;
	sphere.SetCentre(_coordinate);
	sphere.SetRadius(_radius);
	objectArray.push_back(sphere);
	std::cout << "Sphere added?" << std::endl;
}
