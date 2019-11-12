#include "Camera.h"



Camera::Camera(glm::vec2 _screenDimensions)
{
	screenHeight = _screenDimensions.y;
	screenWidth = _screenDimensions.x;

	projectionMatrix = glm::perspective(0.7f, float(screenWidth / screenHeight), 1.0f, 100.0f);
	std::cout << "LOG: Camera created" << std::endl;
}


Camera::~Camera()
{
}

Ray Camera::CalculateRay(glm::ivec2 _pixelCoordPair)
{


	glm::vec4 farPlaneCoord, nearPlaneCoord;

	float ndcX = (_pixelCoordPair.x * (2.0f / screenWidth)) -1.0f;
	float ndcY = (_pixelCoordPair.y * (2.0f / screenHeight)-1.0f)*-1;


	//std::cout << "ndcX" << ndcX << std::endl;
	//std::cout << "ndcY" << ndcY << std::endl;

	farPlaneCoord = { ndcX,ndcY,1.0f, 1.0f };
	nearPlaneCoord = { ndcX,ndcY,-1.0f, 1.0f };

	glm::vec4 farEyeSpace = glm::inverse(projectionMatrix)*farPlaneCoord;
	glm::vec4 nearEyeSpace = glm::inverse(projectionMatrix)*nearPlaneCoord;

	glm::vec3 lfarEyeSpace = farEyeSpace / farEyeSpace.w;
	glm::vec3 lnearEyeSpace = nearEyeSpace / nearEyeSpace.w;

	Ray ray;
	ray.origin = lnearEyeSpace;
	ray.direction = glm::normalize(lfarEyeSpace - lnearEyeSpace);

	return ray;

	/*
	Note: we will define our sphere objects in world-space to make life easy. 
	If you define other objects and you wish to move them, 
	you will need to multiply any object coordinates defined in a 
	local space by the object’s model matrix to get them into world space
	*/
}

Ray Camera::SimpleRay(glm::ivec2 _pixelCoordPair)
{
	Ray ray;
	ray.origin = glm::vec3(_pixelCoordPair, 0);
	ray.direction = glm::vec3(0, 0, 1);
	return ray;
}


