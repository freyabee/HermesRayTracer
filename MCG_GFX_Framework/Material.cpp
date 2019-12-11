#include "Material.h"



Material::Material()
{
	mirror = false;
}

Material::Material(glm::vec3 _albedo)
{
	albedo = _albedo;
	mirror = false;
}

Material::Material(bool _mirror)
{
	albedo = glm::vec3(0.0f, 0.0f, 0.0f);
	mirror = _mirror;
}

Material::Material(float _r, float _g, float _b)
{
	mirror = false;
	SetAlbedoFromRaw(_r, _g, _b);
}


Material::~Material()
{
}

void Material::SetMirror(bool _mirror)
{
	mirror = _mirror;
}

void Material::SetAlbedo(glm::vec3 _albedo)
{
	albedo = _albedo;
}

void Material::SetAlbedoFromRaw(glm::vec3 _albedo)
{
	albedo = _albedo / 255.0f;
}

void Material::SetAlbedoFromRaw(float r, float g, float b)
{
	albedo = glm::vec3(r / 255.0f, g / 255.f, b / 255.f);
}

glm::vec3 Material::GetAlbedo()
{
	return albedo;
}

bool Material::GetMirror()
{


	return mirror;
}
