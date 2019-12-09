#include "Collision.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::SetCollided(bool _b)
{
	collided = _b;
}

void Collision::SetCollisionDistance(float _dist)
{
	collisionDistance = _dist;
}

void Collision::SetCollisionPoint(glm::vec3 _point)
{
	collisionPoint = _point;
}

void Collision::SetCollisionNormal(glm::vec3 _normal)
{
	collisionNormal = _normal;
}

void Collision::SetHitObject(std::shared_ptr<Object> _obj)
{
	hitObject = _obj;
}

bool Collision::GetCollided()
{
	return collided;
}

float Collision::GetCollisionDist()
{
	return collisionDistance;
}

glm::vec3 Collision::GetCollisionPoint()
{
	return collisionPoint;
}

glm::vec3 Collision::GetCollisionNormal()
{
	
	return glm::normalize(collisionNormal);
}

std::shared_ptr<Object> Collision::GetHitObject()
{
	return hitObject;
}
