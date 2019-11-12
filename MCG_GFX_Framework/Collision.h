#pragma once

#include "MCG_GFX_Lib.h"
class Collision
{
public:
	Collision();
	~Collision();
	void setCollided(bool _b);
	void setCollisionDistance(float _dist);
	void setCollisionPoint(glm::vec3 _point);


	bool GetCollided();
	float GetCollisionDist();
	glm::vec3 GetCollisionPoint();
private:
	bool collided;
	float collisionDistance;
	glm::vec3 collisionPoint;


};

