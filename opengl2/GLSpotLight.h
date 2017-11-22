#pragma once
#include "GLBaseLight.h"
class CGLSpotLight :
	public CGLBaseLight
{
public:
	typedef glm::vec3 vec3;
	CGLSpotLight(vec3 SpotDir,float cutoff,float outercutOff,vec3 amb,vec3 diff,vec3 spec);
	~CGLSpotLight();
};

