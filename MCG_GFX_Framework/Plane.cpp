#include "Plane.h"
#include "Collision.h"
#include "Ray.h"
#include "DirectionalLight.h"

#include <memory>

Plane::Plane()
{
}

Plane::Plane(glm::vec3 _coordinate, glm::vec3 _normal)
{
	coordinate = _coordinate;
	normal = _normal;
}


Plane::~Plane()
{
}


Collision Plane::Intersection(Ray _ray)
{
	Collision rtn;
	//a = ray.origin n = ray.dir
	if (glm::dot(normal, _ray.direction)>1e-6)
	{

		float p1 = glm::dot((coordinate - _ray.origin), normal);
		p1 = p1 / (dot(_ray.direction, normal));


		glm::vec3 point = _ray.origin + (p1 * _ray.direction);



		if (p1 > 0.0f)
		{
			rtn.setCollisionPoint(point);
			rtn.setCollided(true);

			float dist = glm::distance(point, _ray.origin);
			rtn.setCollisionDistance(dist);
			return rtn;
		}


	}
	{
		//std::cout << "Plane not intersected" << std::endl;
		rtn.setCollided(false);
		return rtn;
	}
}

glm::vec3 Plane::DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> light)
{
	glm::vec3 hitPoint = _col.GetCollisionPoint();
	glm::vec3 hitNormal = -normal;
	glm::vec3 lightVec = (light->GetDirection());
	
	glm::vec3 hitColor = (light->GetIntensity()*light->GetColor())* std::max(0.f, glm::dot(hitNormal, lightVec));
	return hitColor;
}

void Plane::SetCoordinate(glm::vec3 _coordinate)
{
	coordinate = _coordinate;
}

void Plane::SetNormal(glm::vec3 _normal)
{
	normal = _normal;
}

glm::vec3 Plane::GetCoordinate()
{
	return coordinate;
}

glm::vec3 Plane::GetNormal()
{
	return normal;
}
