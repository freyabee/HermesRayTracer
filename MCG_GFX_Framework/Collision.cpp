#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::setCollided(bool _b)
{
	collided = _b;
}

void Collision::setCollisionDistance(float _dist)
{
	collisionDistance = _dist;
}

void Collision::setCollisionPoint(glm::vec3 _point)
{
	collisionPoint = _point;
}
