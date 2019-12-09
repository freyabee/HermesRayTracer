#pragma once
#include "MCG_GFX_Lib.h"
class Ray
{
private:
public:
	glm::vec3 origin;
	glm::vec3 direction;

	glm::vec3 GetDirection();
	glm::vec3 GetOrigin();
	Ray();
	~Ray();
};

