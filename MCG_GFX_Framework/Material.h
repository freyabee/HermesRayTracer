#pragma once
#include "MCG_GFX_Lib.h"
#include <string>

class Material
{
public:
	Material();
	Material(glm::vec3 _albedo);
	Material(bool _mirror);

	~Material();
	//setters
	void SetMirror(bool _mirror);
	void SetAlbedo(glm::vec3 _albedo);
	//getters
	glm::vec3 GetAlbedo();
	bool GetMirror();

private:
	glm::vec3 albedo;
	glm::vec3 color;
	//does
	bool mirror = false;
	std::string type;
};

