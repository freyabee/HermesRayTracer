#include "Material.h"



Material::Material()
{
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

glm::vec3 Material::GetAlbedo()
{
	return albedo;
}

bool Material::GetMirror()
{


	return mirror;
}
