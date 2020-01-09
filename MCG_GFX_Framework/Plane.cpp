#include "Plane.h"
#include "Collision.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "Material.h"
#include <memory>

Plane::Plane()
{
}

Plane::Plane(glm::vec3 _coordinate, glm::vec3 _normal)
{
	centre = _coordinate;
	normal = _normal;
}

Plane::Plane(glm::vec3 _centre, glm::vec3 _normal, std::shared_ptr<Material> _material)
{
	centre = _centre;
	normal = _normal;
	material = _material;
}

Plane::~Plane()
{
}

Collision Plane::Intersection(Ray _ray)
{
	Collision rtn;
	//a = ray.origin n = ray.dir
	if (glm::dot(-normal, _ray.direction)>1e-6)
	{

		float p1 = glm::dot((centre-_ray.origin), normal);
		p1 = p1 / (dot(_ray.direction, normal));


		glm::vec3 point = _ray.origin + (p1 * _ray.direction);



		if (p1 > 0.0f)
		{
			rtn.SetCollisionPoint(point);
			rtn.SetCollisionNormal(normal);
			rtn.SetCollided(true);
			float dist = glm::distance(point, _ray.origin);
			rtn.SetCollisionDistance(dist);
			return rtn;
		}


	}
	{
		//std::cout << "Plane not intersected" << std::endl;
		rtn.SetCollided(false);
		return rtn;
	}
}

Collision Plane::SIntersection(Ray _ray)
{
	Collision rtn;
	//a = ray.origin n = ray.dir
	if (glm::dot(-normal, _ray.direction)>1e-6)
	{

		float p1 = glm::dot((centre - _ray.origin), normal);
		p1 = p1 / (dot(_ray.direction, normal));


		glm::vec3 point = _ray.origin + (p1 * _ray.direction);



		if (p1 > 0.0f)
		{
			rtn.SetCollisionPoint(point);
			rtn.SetCollisionNormal(normal);
			rtn.SetCollided(true);
			float dist = glm::distance(point, _ray.origin);
			rtn.SetCollisionDistance(dist);
			return rtn;
		}


	}
	{
		rtn.SetCollided(false);
		return rtn;
	}

}

glm::vec3 Plane::ReturnSurfaceNormal(Collision _col)
{
	return normal;
}

glm::vec3 Plane::DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> _dlight, glm::vec3 _plVec, bool _inShadow)
{

	glm::vec3 hitPoint = _col.GetCollisionPoint();
	glm::vec3 hitNormal = normal;
	glm::vec3 lightVec = (_dlight->GetDirection())*1.0f;
	glm::vec3 light(0.f, 0.f, 0.f);

	if (_inShadow)
	{
		
	}
	else
	{
		light = _dlight->GetIntensity() * _dlight->GetColor() * std::max(0.f, glm::dot(hitNormal, -lightVec));
	}
	


	//glm::vec3 light = _dlight->GetIntensity() * _dlight->GetColor() * std::max(0.f, glm::dot(hitNormal, lightVec));

	light += _plVec;

	glm::vec3 hitColor = (material->GetAlbedo() / glm::pi<float>()) * light;


	return hitColor;
}

glm::vec3 Plane::NormalShader(Ray _ray, Collision _col)
{
	glm::vec3 n = ReturnSurfaceNormal(_col);
	glm::vec3 rtn;
	n = 0.5f*n;

	rtn.x = n.x+1.0f;
	rtn.y = n.y+1.0f;
	rtn.z = n.z+1.0f;
	return rtn;
}

glm::vec3 Plane::DebugShader()
{
	return glm::vec3(1.0f,0.f,0.f);
}
 

void Plane::SetCentre(glm::vec3 _coordinate)
{
	centre = _coordinate;
}

void Plane::SetNormal(glm::vec3 _normal)
{
	normal = _normal;
}

void Plane::SetMaterial(std::shared_ptr<Material> _material)
{
	material = _material;
}

glm::vec3 Plane::GetCentre()
{
	return centre;
}

glm::vec3 Plane::GetNormal()
{
	return normal;
}

std::shared_ptr<Material> Plane::GetMaterial()
{
	return material;
}
