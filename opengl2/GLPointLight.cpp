#include "GLPointLight.h"
#include"GLFactory.h"
CGLPointLight::CGLPointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic):CGLBaseLight(amb,diff,spec,"pointLight[0]")
{

	CGLFactory::GetInstance()->AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetFloat("pointLight[0].constant", constant);
		sptr->SetFloat("pointLight[0].linear", linear);
		sptr->SetFloat("pointLight[0].quadratic", quadratic);
	});
}

CGLPointLight::~CGLPointLight()
{
}

