#pragma once
#include "MCG_GFX_Lib.h"
#include <string>

class Material
{
public:
	Material();
	Material(glm::vec3 _albedo);
	Material(bool _mirror);
	//Set 255 rgb values
	Material(float _r, float _g, float _b);

	~Material();
	//setters
	void SetMirror(bool _mirror);
	void SetAlbedo(glm::vec3 _albedo);
	void SetAlbedoFromRaw(glm::vec3 _albedo);
	void SetAlbedoFromRaw(float r, float g, float b);
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

