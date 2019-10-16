#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
class Camera
{
public:
	Camera();
	~Camera();
	Ray CalculateRay(glm::ivec2 _pixelCoordPair);
};

