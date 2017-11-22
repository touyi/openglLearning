#pragma once
#include "GLBaseLight.h"
class CGLPointLight :
	public CGLBaseLight
{
public:
	CGLPointLight(glm::vec3 amb,glm::vec3 diff,glm::vec3 spec,float constant,float linear,float quadratic);
	~CGLPointLight();
private:
	float constant;
	float linear;
	float quadratic;
};

