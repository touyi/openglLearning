#pragma once
#include "GLBaseLight.h"
class CGLDirctionLight :
	public CGLBaseLight
{
public:
	CGLDirctionLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec,glm::vec3 dir);
	~CGLDirctionLight();
private:
	glm::vec3 lightDir;
};

