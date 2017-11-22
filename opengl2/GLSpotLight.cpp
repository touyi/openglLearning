#include "GLSpotLight.h"
#include"GLFactory.h"


CGLSpotLight::CGLSpotLight(vec3 SpotDir, float cutoff, float outercutOff, vec3 amb, vec3 diff, vec3 spec):CGLBaseLight(amb,diff,spec,"spotLight")
{
	CGLFactory::AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetVec3("spotLight.SpotDir", SpotDir);
		sptr->SetFloat("spotLight.cutoff", cutoff); 
		sptr->SetFloat("spotLight.outercutOff", outercutOff);
	});
}

CGLSpotLight::~CGLSpotLight()
{
}
