#include "Sphere.h"
#include "DirectionalLight.h"
#include "Collision.h"
#include "Ray.h"
#include "Material.h"
#include "Object.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}



glm::vec3 Sphere::ShadePixel(Ray _ray, Collision _col)
{
	/*
	TODO: Function that shades pixel and returns pixel color in vec3
	*/

	glm::vec3 hitPoint = _col.GetCollisionPoint();
	glm::vec3 surfaceNormal = (_col.GetCollisionPoint() - centre) * (1.0f/radius);
	glm::vec3 normdir= (-_ray.direction);



	float hitColor = glm::max(glm::dot(surfaceNormal, normdir),0.0f);
	pixelColour = glm::vec3(0.9f, 0.0, 0.0);

	glm::vec3 color = pixelColour * (hitColor);

	return (color);
}

glm::vec3 Sphere::DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> light)
{
	//std::shared_ptr<DirectionalLight> dl = light;

	glm::vec3 hitPoint = _col.GetCollisionPoint();
	glm::vec3 hitNormal = (_col.GetCollisionPoint() - centre) * (1.0f / radius);
	glm::vec3 lightVec = (light->GetDirection());
	glm::vec3 hitColor = material->GetAlbedo()/glm::pi<float>() *(light->GetIntensity()*light->GetColor()) * std::max(0.f, glm::dot(hitNormal, lightVec));
	return hitColor;
}


Collision Sphere::Intersection(Ray _ray)
{
	Collision col;
	//Check if ray origin is inside sphere
	if (glm::distance(_ray.origin, centre) <= radius)
	{
		std::cout << "ERROR: Ray origin within circle" << std::endl;
		col.setCollided(false);
		return col;
	}

	//Find closest point on ray to centre of sphere
	glm::vec3 closestPoint = ClosestPoint(_ray, centre);

	//Check if closes point is in front or behind the ray origin/direction - point - ray origin
	if (glm::length(closestPoint - _ray.origin) < 0)
	{
		std::cout << "ERROR: shape behind ray" << std::endl;
		col.setCollided(false);
		return col;
	}

	//Work out distance from closes point to sphere centre (D)
	//vector between centre point and closest point.
	glm::vec3 OriginToCentre = centre - _ray.origin;

	glm::vec3 ClosestPointToCentre = (glm::dot(OriginToCentre, _ray.direction)*_ray.direction);

	glm::vec3 XToCentre = centre - _ray.origin - ClosestPointToCentre;

	//length of vector between centre and closest point X )
	float d = glm::length(XToCentre);

	if (d > radius)
	{
		col.setCollided(false);
		return col;
	}

	//distance between collision point and closest point
	float x = sqrt((radius*radius) - (d*d));

	//first point of intersection (3d vec) 
	glm::vec3 collisionPoint = _ray.origin + (((glm::dot((centre - _ray.origin), _ray.direction)) - x)*_ray.direction);
	float collisionDist = glm::length(collisionPoint - _ray.origin);


	col.setCollided(true);
	col.setCollisionPoint(collisionPoint);
	col.setCollisionDistance(collisionDist);
	return col;
}

void Sphere::SetCentre(glm::vec3 _centre)
{
	centre = _centre;
}

void Sphere::SetRadius(float _radius)
{
	radius = _radius;
}

glm::vec3 Sphere::GetCentre()
{
	return centre;
}

float Sphere::GetRadius()
{
	return radius;
}

void Sphere::SetMaterial(std::shared_ptr<Material> _material)
{
	material = _material;
}

std::shared_ptr<Material> Sphere::GetMaterial()
{
	return material;
}

