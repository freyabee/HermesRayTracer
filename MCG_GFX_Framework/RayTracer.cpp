#include "Plane.h"
#include "Collision.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Object.h"
#include "Camera.h"
#include "Material.h"
#include "Scene.h"

#include <memory>
#include "RayTracer.h"

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
	/* Get all collisions for the ray. */
	std::vector<Collision> collisions = GetCollisions(_ray);



	if (collisions.size() > 0)
	{
		/* Get closest collision from all collisions. */
		Collision hitCol = GetClosestCollision(collisions);

		/* If object material is mirror. */
		if (hitCol.GetHitObject()->GetMaterial()->GetMirror()==true && depth<10)
		{
			/* Trace mirror ray and return it's shaded value */
			return TraceRay(GetReflectionRay(_ray, hitCol), depth + 1)*0.85f;

		}


		/* Calculate if pixel is in shadow from point light. */
		bool shadowed = CalculateShadows(hitCol);


		/* Calculate color input from point lights. */
		glm::vec3 plCumulative = CalculatePointLights(hitCol);
		if (plCumulative != glm::vec3(0.f))
		{
			shadowed = false;
		}


		/* Put values into objects diffuse shader */
		glm::vec3 hitColor = hitCol.GetHitObject()->DiffuseShader(_ray, hitCol, dlArray[0], plCumulative, shadowed);


		/* Debug shaders
		return hitCol.GetHitObject()->NormalShader(_ray, hitCol);
		return hitCol.GetHitObject()->DebugShader();
		*/

		/* Clamp returning hit color between 0 and 1 */
		return glm::clamp(hitColor, glm::vec3(0.0f), glm::vec3(1.0f));
	}
	/* If no collisions found return background color. */
	return backgroundColor;
	
}

/* Stages of the TraceRay function*/

bool RayTracer::CalculateShadows(Collision _col)
{
	Ray sRay;
	Collision sCol;
	sRay.origin = _col.GetCollisionPoint() + (_col.GetCollisionNormal()*0.1f);
	sRay.direction = -dlArray[0]->GetDirection();

	for (int i = 0; i < objectArray.size(); i++)
	{
		if (objectArray[i] != _col.GetHitObject())
		{
			sCol = objectArray[i]->SIntersection(sRay);

			if (sCol.GetCollided() == true && sCol.GetHitObject() != _col.GetHitObject())
			{
				return true;
			}
		}
	}
	return false;

}

glm::vec3 RayTracer::CalculatePointLights(Collision _col)
{
	glm::vec3 plCumulative(0.f, 0.f, 0.f);
	Ray plRay;
	Collision plCol;
	plRay.origin = _col.GetCollisionPoint() + (_col.GetCollisionNormal()*0.1f);


	//For each point in the point light array
	for (int ipl = 0; ipl < plArray.size(); ipl++)
	{
		//plRay points from pixel to light 
		plRay.direction = plArray[ipl]->GetDirection(_col.GetCollisionPoint());
		//For each object in the scene
		for (int i = 0; i < objectArray.size(); i++)
		{
			//Check collision on way to light
			plCol = objectArray[i]->SIntersection(plRay);
			if (!plCol.GetCollided() == true)
			{
				glm::vec3 thisLightColor = plArray[ipl]->CalculateShadingInfo(_col);
				plCumulative += thisLightColor;
			}
		}
	}

	return plCumulative;
}

std::vector<Collision> RayTracer::GetCollisions(Ray _ray)
{
	Collision check;
	std::vector<Collision> collisions;
	std::vector<int> collidedElements;


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
	return collisions;
}

Collision RayTracer::GetClosestCollision(std::vector<Collision> _collisions)
{
	int element;
	float smallestDist;


	for (int i = 0; i < _collisions.size(); i++)
	{
		if (i == 0)
		{
			smallestDist = _collisions[i].GetCollisionDist();
			element = i;
		}
		else
		{
			if (smallestDist > _collisions[i].GetCollisionDist())
			{
				smallestDist = _collisions[i].GetCollisionDist();
				element = i;
			}
		}

	}
	Collision rtn = _collisions[element];

	return rtn;
}

Ray RayTracer::GetReflectionRay(Ray _ray, Collision _col)
{
	glm::vec3 hitNormal = _col.GetCollisionNormal();
	glm::vec3 reflectionVec = Reflection(_ray.GetDirection(), hitNormal);
	Ray reflectRay;

	reflectRay.origin = (_col.GetCollisionPoint() + hitNormal * 0.1f);
	reflectRay.direction = glm::normalize(reflectionVec);


	return reflectRay;
}

/* Math helper functions. */

glm::vec3 RayTracer::Reflection(glm::vec3 _rayDir, glm::vec3 _surfaceNormal)
{
	glm::vec3 rtn = _rayDir - 2.0f * glm::dot(_rayDir, _surfaceNormal)*_surfaceNormal;
	return rtn;
}

glm::vec3 RayTracer::ClosestPoint(Ray _ray, glm::vec3 _point)
{
	glm::vec3 temp = glm::dot((_point - _ray.origin), _ray.direction)*_ray.direction;
	return temp;
}

/* Functions for adding objects to scene. */

void RayTracer::AddScene(Scene scene)
{
	std::cout << "** LOADING OBJECTS FROM SCENE **" << std::endl;
	objectArray = scene.GetObjects();
	std::cout << objectArray.size() << " object(s) loaded from scene." << std::endl;
	dlArray = scene.GetDirectionalLights();
	std::cout << dlArray.size() << " directional light(s) loaded from scene." << std::endl;
	plArray = scene.GetPointLights();
	std::cout << plArray.size() << " point lights(s) loaded from scene." << std::endl;
	std::cout << "** OBJECT LOADING COMPLETE **" << std::endl;
}

void RayTracer::AddSphereToScene(glm::vec3 _coordinate, float _radius, std::shared_ptr<Material> _mat)
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();

	sphere->SetMaterial(_mat);
	sphere->SetCentre(_coordinate);
	sphere->SetRadius(_radius);
	objectArray.push_back(sphere);
	std::cout << "Sphere added to scene at (" <<_coordinate.x<<","<<_coordinate.y<<","<<_coordinate.z<<")." << std::endl;

}

void RayTracer::AddDirectionalLightToScene(glm::vec3 _color, glm::vec3 _direction, float _intensity)
{
	std::shared_ptr<DirectionalLight> dl = std::make_shared<DirectionalLight>();
	dl->SetDirection(_direction);
	dl->SetColor(_color);
	dl->SetIntensity(_intensity);
	dlArray.push_back(std::move(dl));
	std::cout << "Directional light added to scene." << std::endl;
}

void RayTracer::AddPlaneToScene(glm::vec3 _coordinate, glm::vec3 _normal, std::shared_ptr<Material> _material)
{
	std::shared_ptr<Plane> plane = std::make_shared<Plane>(_coordinate, _normal);
	plane->SetMaterial(_material);
	objectArray.push_back(std::move(plane));
	std::cout << "Plane added to scene at (" << _coordinate.x << "," << _coordinate.y << "," << _coordinate.z << ")." << std::endl;
}

void RayTracer::AddPointLightToScene(glm::vec3 _centre, float _intensity, glm::vec3 _color)
{
	std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(_centre, _intensity, _color);
	plArray.push_back(std::move(pl));
	std::cout << "Point light added to scene at (" << _centre.x << "," << _centre.y << "," << _centre.z << ")." << std::endl;

}

