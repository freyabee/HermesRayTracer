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

glm::vec3 Sphere::DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> _light, bool _inShadow)
{
	if (_inShadow)
	{
		return glm::vec3(0.1f, 0.1f, 0.1f);
	}
	//glm::vec3 colNormal = _col.GetCollisionNormal();
	glm::vec3 colNormal = ReturnSurfaceNormal(_col);

	glm::vec3 lightVec = -_light->GetDirection();
	//lightVec = glm::normalize(lightVec);
	

	glm::vec3 hitColor = material->GetAlbedo()/glm::pi<float>() * (_light->GetIntensity() * _light->GetColor()) * std::max(0.f, glm::dot(colNormal, lightVec));


	return hitColor;
}

glm::vec3 Sphere::NormalShader(Ray _ray, Collision _col)
{
	glm::vec3 n = _col.GetCollisionNormal();
	glm::vec3 rtn;
	n = 0.5f*n;
	rtn.x = n.x+1.0f;
	rtn.y = n.y+1.0f;
	rtn.z = n.z+1.0f;
	return rtn;

}

glm::vec3 Sphere::DebugShader()
{
	return glm::vec3(1.f,0.f,0.f);
}

Collision Sphere::Intersection(Ray _ray)
{
	Collision col;
	double distance = glm::distance(_ray.origin, centre);
	//Check if ray origin is inside sphere
	if (distance < radius)
	{
		std::cout << "ERROR: Ray origin within circle" << std::endl;
		col.SetCollided(false);
		return col;
	}

	//Find closest point on ray to centre of sphere
	glm::vec3 closestPoint = ClosestPoint(_ray, centre);

	//Check if closes point is in front or behind the ray origin/direction - point - ray origin
	if (glm::length(closestPoint - _ray.origin) < 0)
	{
		std::cout << "ERROR: shape behind ray" << std::endl;
		col.SetCollided(false);
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
		col.SetCollided(false);
		return col;
	}

	//distance between collision point and closest point
	float x = sqrt((radius*radius) - (d*d));

	//first point of intersection (3d vec) 
	glm::vec3 collisionPoint = _ray.origin + (((glm::dot((centre - _ray.origin), _ray.direction)) - x)*_ray.direction);
	float collisionDist = glm::length(collisionPoint - _ray.origin);


	col.SetCollided(true);
	col.SetCollisionPoint(collisionPoint);
	col.SetCollisionDistance(collisionDist);
	return col;
}

Collision Sphere::SIntersection(Ray _ray)
{

	Collision rtn;
	glm::vec3 oc = _ray.origin - centre;
	float a = glm::dot(_ray.GetDirection(), _ray.GetDirection()); //a = 1
	float b = 2.0f * glm::dot(oc, _ray.direction);		//b = 2*D*(O-C)
	float c = glm::dot(oc,oc) - (radius * radius);//c = |O-C|^2 - R



	float t0;
	float t1;
	float t;


	float discr = b * b - 4 * a * c;

	bool intersect;


	if (discr < 0) {
		rtn.SetCollided(false);
		return rtn;
	}
	else if (discr == 0) 
	{
		t0 = t1 = -0.5 * b / a;
		intersect = true;
	} 
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
		intersect = true;
	}


	if (t0 > t1)
	{
		std::swap(t0, t1);

	}





	if (intersect==true)
	{
		if (t0 > t1) std::swap(t0, t1);
		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
			{
				rtn.SetCollided(false);
			}
		}
		t = t0;
		glm::vec3 collisionPoint = _ray.origin + (t0*_ray.GetDirection());	// O +t0*D
		glm::vec3 collisionNormal = glm::normalize(collisionPoint - centre); // ||Phit-C||
		float collisionDistance = glm::distance(_ray.origin, collisionPoint);
		rtn.SetCollided(true);
		rtn.SetCollisionPoint(collisionPoint);
		rtn.SetCollisionNormal(collisionNormal);
		rtn.SetCollisionDistance(collisionDistance);
		return rtn;
	}
	else
	{
		rtn.SetCollided(false);
	}

	/*
	if (discriminant > 0)
	{
		float t0 = -(b + sqrt(discriminant)) / (2 * a); // -b + _/discrim / 2a
		float t1 = -(b - sqrt(discriminant)) / (2 * a); // -b - _/discrim /2a

		glm::vec3 collisionPoint = _ray.origin + (t0*_ray.direction);	// O +t0*D
		glm::vec3 collisionNormal = glm::normalize(collisionPoint - centre); // ||Phit-C||
		rtn.SetCollided(true);
		rtn.SetCollisionPoint(collisionPoint);
		rtn.SetCollisionNormal(collisionNormal);
		return rtn;
	}
	else if (discriminant == 0) //1 discriminant == tangent collision
	{
		float t0 = -(b / (2 * a));
		glm::vec3 collisionPoint = _ray.origin + (t0*_ray.direction);	// O +t0*D
		glm::vec3 collisionNormal = glm::normalize(collisionPoint - centre); // ||Phit-C||
		float collisionDistance = glm::distance(_ray.origin, centre);

		//Set collision object variables
		rtn.SetCollided(true);
		rtn.SetCollisionPoint(collisionPoint);
		rtn.SetCollisionNormal(collisionNormal);
		rtn.SetCollisionDistance(collisionDistance);
		//return collision object
		return rtn;
	}
	else
	{
		rtn.SetCollided(false);
		return rtn;
	}
	*/


}

bool Sphere::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}

glm::vec3 Sphere::ReturnSurfaceNormal(Collision _col)
{
	glm::vec3 rtn;
	rtn =( _col.GetCollisionPoint() - centre )* (1.0f / radius);
	rtn = glm::normalize(rtn);
	return rtn;
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

