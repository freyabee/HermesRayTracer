#include "MCG_GFX_Lib.h"
#include <memory>
#include "Object.h"
//Referenced classes
class Collision;
class Ray;
class DirectionalLight;
class Material;


class Plane : public Object
{

public:

	Plane();
	Plane(glm::vec3 _coordinate, glm::vec3 _normal);
	Plane(glm::vec3 _coordinate, glm::vec3 _normal, std::shared_ptr<Material> _material);
	~Plane();
	//Collision
	Collision Intersection(Ray _ray);
	Collision SIntersection(Ray _ray);
	glm::vec3 ReturnSurfaceNormal(Collision _col);
	//Shader
	glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> _light, glm::vec3 _plVec, bool _inShadow);
	glm::vec3 NormalShader(Ray _ray, Collision _col);
	glm::vec3 DebugShader();
	//Setters
	void SetCentre(glm::vec3 _coordinate);
	void SetNormal(glm::vec3 _normal);
	void SetMaterial(std::shared_ptr<Material> _material);
	//Getters
	glm::vec3 GetCentre();
	glm::vec3 GetNormal();
	std::shared_ptr<Material> GetMaterial();
	
private:
	glm::vec3 centre;
	glm::vec3 normal;
	std::shared_ptr<Material> material;

};

