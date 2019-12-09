#pragma once

#include "MCG_GFX_Lib.h"
#include <memory>

class Object;

class Collision
{
public:
	Collision();
	~Collision();
	//setters
	
	void SetCollided(bool _b);
	void SetCollisionDistance(float _dist);
	void SetCollisionPoint(glm::vec3 _point);
	void SetCollisionNormal(glm::vec3 _normal);
	void SetHitObject(std::shared_ptr<Object> _obj);

	//getss
	bool GetCollided();
	float GetCollisionDist();
	glm::vec3 GetCollisionPoint();
	glm::vec3 GetCollisionNormal();
	std::shared_ptr<Object> GetHitObject();
private:
	bool collided;
	float collisionDistance;
	glm::vec3 collisionPoint;
	glm::vec3 collisionNormal;
	std::shared_ptr<Object> hitObject;

};

