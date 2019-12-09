#include "Ray.h"



glm::vec3 Ray::GetDirection()
{
	return glm::normalize(direction);
}

glm::vec3 Ray::GetOrigin()
{
	return origin;
}

Ray::Ray()
{
}


Ray::~Ray()
{
}
