#include "RayTracer.h"
#include <memory>
#include "Plane.h"
#include "Collision.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "Object.h"
#include "Camera.h"
#include "Material.h"

RayTracer::RayTracer()
{
}

RayTracer::RayTracer(glm::vec3 _backgroundColor)
{
	backgroundColor = _backgroundColor;
}



RayTracer::~RayTracer()
{
}

glm::vec3 RayTracer::TraceRay(Ray _ray, int depth)
{
	Collision check;


	std::vector<Collision> collisions;
	std::vector<int> collidedElements;

	bool collided = false;

	for (int i = 0; i < objectArray.size(); i++)
	{
		check = objectArray[i]->SIntersection(_ray);
		check.SetHitObject(objectArray[i]);

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

		// closest Object and object collision
		Collision hitCol = collisions[element];



		
		
		//if hit object is mirror
		if (hitCol.GetHitObject()->GetMaterial()->GetMirror()==true && depth<3)
		{

			//cast ray in reflection direction
			glm::vec3 hitNormal = hitCol.GetCollisionNormal();
			glm::vec3 reflectionVec = Reflection(_ray.GetDirection(), hitNormal);
			Ray reflectRay;

			reflectRay.origin = (hitCol.GetCollisionPoint()+hitNormal*0.1f);
			reflectRay.direction = glm::normalize(reflectionVec);


			return TraceRay(reflectRay, depth + 1)*0.85f;

		}


		//SHADOWS//

		bool shadowed = false;


		Ray sRay;
		Collision sCol;
		sRay.origin = hitCol.GetCollisionPoint() + (hitCol.GetCollisionNormal()*0.1f);
		sRay.direction = glm::vec3(0.0f, 1.0f, 0.0f);

			for (int i = 0; i < objectArray.size(); i++)
			{
				if (objectArray[i] != hitCol.GetHitObject())
				{
					sCol = objectArray[i]->SIntersection(sRay);

					if (sCol.GetCollided() == true && sCol.GetHitObject() != hitCol.GetHitObject())
					{
						shadowed = true;
					}
				}
			}

		
		
		
		//return hitCol.GetHitObject()->NormalShader(_ray, hitCol);
		//return hitCol.GetHitObject()->DebugShader();
		glm::vec3 hitColor = hitCol.GetHitObject()->DiffuseShader(_ray, hitCol, dlArray[0], shadowed);

		
		return glm::clamp(hitColor, glm::vec3(0.0f), glm::vec3(1.0f));
	}

	//Else return background
	return backgroundColor;
	
}

glm::vec3 RayTracer::ClosestPoint(Ray _ray, glm::vec3 _point)
{
	glm::vec3 temp = glm::dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}

Collision RayTracer::GetShadows(int element, Collision _col, std::shared_ptr<Object> obj)
{
	Collision shadowCol;
	Ray shadowRay;


	shadowRay.origin = (_col.GetCollisionPoint() + (obj->ReturnSurfaceNormal(_col)));
	shadowRay.direction = glm::vec3(0.f, 1.f, 0.f);


	//return obj->Intersection(shadowRay);


	for (int i = 0; i < objectArray.size(); i++)
	{
		if (element != i)
		{
			shadowCol = objectArray[i]->Intersection(shadowRay);
			if (shadowCol.GetCollided() == true)
			{
				
				shadowCol.SetHitObject(objectArray[i]);
				return shadowCol;
			}

		}
	}
	shadowCol.SetCollided(false);
	return shadowCol;

}

glm::vec3 RayTracer::Reflection(glm::vec3 _rayDir, glm::vec3 _surfaceNormal)
{
	glm::vec3 rtn = _rayDir - 2.0f * glm::dot(_rayDir, _surfaceNormal)*_surfaceNormal;
	return rtn;
}

void RayTracer::AddSphereToScene(glm::vec3 _coordinate, float _radius, std::shared_ptr<Material> _mat)
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();

	sphere->SetMaterial(_mat);
	sphere->SetCentre(_coordinate);
	sphere->SetRadius(_radius);
	objectArray.push_back(sphere);
	std::cout << "Sphere added." << std::endl;

}

void RayTracer::AddDirectionalLightToScene(glm::vec3 _color, glm::vec3 _direction, float _intensity)
{
	std::shared_ptr<DirectionalLight> dl = std::make_shared<DirectionalLight>();
	dl->SetDirection(_direction);
	dl->SetColor(_color);
	dl->SetIntensity(_intensity);
	dlArray.push_back(std::move(dl));
}

void RayTracer::AddPlaneToScene(glm::vec3 _coordinate, glm::vec3 _normal, std::shared_ptr<Material> _material)
{
	std::shared_ptr<Plane> plane = std::make_shared<Plane>(_coordinate, _normal);
	plane->SetMaterial(_material);
	objectArray.push_back(std::move(plane));
}

