#pragma once
#include "MCG_GFX_Lib.h"
class Material
{
public:
	Material();
	Material(glm::vec3 _albedo);

	~Material();

	glm::vec3 GetAlbedo();
private:
	glm::vec3 albedo;
	glm::vec3 color;
};

