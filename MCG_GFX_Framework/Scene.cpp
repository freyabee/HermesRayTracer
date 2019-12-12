#include "Scene.h"

#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLight.h"
#include "DirectionalLight.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddSphereToScene(glm::vec3 _centre, float _radius,  std::shared_ptr<Material> _material)
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(_centre, _material, _radius);
	sceneObjects.emplace_back(std::move(sphere));
}

void Scene::AddSphereToScene(float _x, float _y, float _z, float _radius, std::shared_ptr<Material> _material)
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(_x, _y, _z), _material, _radius);
	sceneObjects.emplace_back(std::move(sphere));
}

void Scene::AddPlaneToScene(glm::vec3 _centre, glm::vec3 _normal, std::shared_ptr<Material> _material)
{
	std::shared_ptr<Plane> plane = std::make_shared<Plane>(_centre, _normal, _material);
	sceneObjects.emplace_back(std::move(plane));
}

void Scene::AddPlaneToScene(float _x, float _y, float _z, float _nX, float _nY, float _nZ, std::shared_ptr<Material> _material)
{
	std::shared_ptr<Plane> plane = std::make_shared<Plane>(glm::vec3(_x, _y, _z), glm::vec3(_nX, _nY, _nZ), _material);
	sceneObjects.emplace_back(std::move(plane));
}

void Scene::AddPointLightToScene(glm::vec3 _centre, float _intensity,  std::shared_ptr<Material> _material)
{
	std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(_centre, _intensity, _material->GetAlbedo());
	scenePls.emplace_back(std::move(pl));
}

void Scene::AddDirectionalLightToScene(glm::vec3 _direction, float _intensity, std::shared_ptr<Material> _material)
{
	std::shared_ptr<DirectionalLight> dl = std::make_shared<DirectionalLight>(_intensity, _direction, _material->GetAlbedo());
	sceneDls.emplace_back(std::move(dl));
}

std::vector<std::shared_ptr<Object>> Scene::GetObjects()
{
	return sceneObjects;
}

std::vector<std::shared_ptr<DirectionalLight>> Scene::GetDirectionalLights()
{
	return sceneDls;
}

std::vector<std::shared_ptr<PointLight>> Scene::GetPointLights()
{
	return scenePls;
}
