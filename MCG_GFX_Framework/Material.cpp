#include "Material.h"



Material::Material()
{
}

Material::Material(glm::vec3 _albedo)
{
	albedo = _albedo;
}


Material::~Material()
{
}

glm::vec3 Material::GetAlbedo()
{
	return albedo;
}
