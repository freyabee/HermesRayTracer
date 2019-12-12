#pragma once
#include <memory>
#include <vector>
#include "MCG_GFX_Lib.h"

class Object;
class Material;
class Sphere;
class Plane;
class PointLight;
class DirectionalLight;


class Scene
{
public:
	Scene();
	~Scene();

	void AddSphereToScene(glm::vec3 _centre, float _radius, std::shared_ptr<Material> _material);
	void AddSphereToScene(float _x, float _y, float _z,  float _radius, std::shared_ptr<Material> _material);
	void AddPlaneToScene(glm::vec3 _centre, glm::vec3 _normal, std::shared_ptr<Material> _material);
	void AddPlaneToScene(float _x, float _y, float _z, float _nX, float _nY, float _nZ, std::shared_ptr<Material> _material);
	void AddPointLightToScene(glm::vec3 _centre, float _intensity, std::shared_ptr<Material> _material);
	void AddDirectionalLightToScene(glm::vec3 _direction, float _intensity, std::shared_ptr<Material> _material);

	std::vector<std::shared_ptr<Object>> GetObjects();
	std::vector<std::shared_ptr<DirectionalLight>> GetDirectionalLights();
	std::vector<std::shared_ptr<PointLight>> GetPointLights();

private:
	std::vector <std::shared_ptr<Object>> sceneObjects;
	std::vector <std::shared_ptr<DirectionalLight>> sceneDls;
	std::vector < std::shared_ptr<PointLight>> scenePls;

};

