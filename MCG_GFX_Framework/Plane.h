#include "MCG_GFX_Lib.h"
#include <memory>
#include "Object.h"
//Referenced classes
class Collision;
class Ray;
class DirectionalLight;



class Plane : public Object
{

public:

	Plane();
	Plane(glm::vec3 _coordinate, glm::vec3 _normal);
	~Plane();
	//Collision
	Collision Intersection(Ray _ray);
	//Shader
	glm::vec3 DiffuseShader(Ray _ray, Collision _col, std::shared_ptr<DirectionalLight> light);
	//Setters
	void SetCoordinate(glm::vec3 _coordinate);
	void SetNormal(glm::vec3 _normal);
	//Getters
	glm::vec3 GetCoordinate();
	glm::vec3 GetNormal();
	
private:
	glm::vec3 coordinate;
	glm::vec3 normal;
};

