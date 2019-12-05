#include "RayTracer.h"
#include <memory>

RayTracer::RayTracer()
{
}


RayTracer::~RayTracer()
{
}

glm::vec3 RayTracer::TraceRay(Ray _ray)
{
	//go through all objects in scene 
	

	float distHold = 9999;
	bool col = false;
	Collision check;

	std::vector<Collision> collisions;
	std::vector<int> collidedElements;

	bool collided = false;
	for (int i = 0; i < objectArray.size(); i++)
	{

		check = SphereIntersection(_ray, objectArray.at(i)->GetCentre(), objectArray.at(i)->GetRadius());
		if (check.GetCollided() == true)
		{
			collidedElements.push_back(i);
			collisions.push_back(check);
		}
	}


	if (collisions.size() > 0)
	{
		int element;
		float smallestDist;


		for (int i = 0; i < collisions.size(); i++)
		{
			if (i == 0)
			{
				smallestDist = collisions[i].GetCollisionDist();
				element = i;
			}
			else
			{
				if (smallestDist > collisions[i].GetCollisionDist())
				{
					smallestDist = collisions[i].GetCollisionDist();
					element = i;
				}
			}

		}


		return objectArray[collidedElements[element]]->ShadePixel(_ray, collisions[element]);

	}
	






	
	
	if (collided==true)
	{
		float dist = 999;
		int closestObj = NULL;

		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions[i].GetCollided() == true)
			{
				
				

				if (i == 0)
				{
					dist = collisions[i].GetCollisionDist();
					closestObj = i;
				}
				else
				{
					if (dist > collisions[i].GetCollisionDist())
					{
						dist = collisions[i].GetCollisionDist();
						closestObj = i;
					}
				}


				
			}
		}

		if (closestObj != NULL)
		{
			return objectArray[closestObj]->ShadePixel(_ray, check);
		}
		

	}

	return glm::vec3(0.0f, 0.0f, 0.0f);
	
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


	
	if (d > _radius)
	{
		sphereCol.setCollided(false);
		return sphereCol;
	}
	else
	{
	}

	//distance between collision point and closest point
	float x = sqrt((_radius*_radius) - (d*d));


	//first point of intersection (3d vec) 
	glm::vec3 col = _ray.origin+(((glm::dot((_centre - _ray.origin), _ray.direction)) - x)*_ray.direction);

	float collisionDist = glm::length(col - _ray.origin);
	sphereCol.setCollided(true);
	sphereCol.setCollisionPoint(col);
	sphereCol.setCollisionDistance(collisionDist);
	return sphereCol;
}
void RayTracer::AddSphereToScene(glm::vec3 _coordinate, float _radius)
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->SetCentre(_coordinate);
	sphere->SetRadius(_radius);
	objectArray.push_back(sphere);
	std::cout << "Sphere added." << std::endl;
}

void RayTracer::AddLightToScene(glm::vec3 _coordinate, float _radius)
{
	std::shared_ptr<Light> light = std::make_shared<Light>();
	light->SetCentre(_coordinate);
	light->SetRadius(_radius);
	objectArray.push_back(std::move(light));
	std::cout << "Light added." << std::endl;
}
