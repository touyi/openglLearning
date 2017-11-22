#pragma once
#include<GLM\glm.hpp>
#include<GLM\gtc\matrix_transform.hpp>
#include<GLM\gtc\type_ptr.hpp>
#include<string>
class CGLBaseLight
{
public:
	enum ValueType
	{
		LightDir,
		Ambient,
		Diffuse,
		Specular,
		Position,
		SpotDir
	};
	CGLBaseLight(glm::vec3 amb,glm::vec3 diff,glm::vec3 spec,std::string lightName);
	CGLBaseLight() = default;
	virtual ~CGLBaseLight();
	virtual void SetVec3(glm::vec3&, std::string);
	virtual void SetFloat(float value, std::string var);
protected:
	std::string lightName;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

