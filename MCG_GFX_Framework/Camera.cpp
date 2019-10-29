#include "Camera.h"



Camera::Camera(glm::vec2 _screenDimensions)
{
	screenHeight = _screenDimensions.y;
	screenWidth = _screenDimensions.x;

	std::cout << "LOG: Camera created" << std::endl;
}


Camera::~Camera()
{
}

Ray Camera::CalculateRay(glm::ivec2 _pixelCoordPair)
{
	glm::vec4 farPlaneCoord, nearPlaneCoord;

	float ndcX = (_pixelCoordPair.x * (2.0f / screenWidth)) -1.0f;
	float ndcY = (_pixelCoordPair.y * (2.0f / screenHeight)) + 1.0f;

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

}


