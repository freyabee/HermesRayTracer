#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include <iostream>

class Camera
{
public:
	Camera(glm::vec2 _screenDimensions);
	~Camera();
	Ray CalculateRay(glm::ivec2 _pixelCoordPair);
private:
	glm::mat4 viewingMatrix;
	glm::mat4 projectionMatrix;
	int screenHeight;
	int screenWidth;
};

