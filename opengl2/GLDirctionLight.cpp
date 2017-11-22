#include "GLDirctionLight.h"
#include"GLFactory.h"


CGLDirctionLight::CGLDirctionLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir):
	CGLBaseLight(amb, diff, spec,"dirlight"),
	lightDir(dir)

{
	CGLFactory::AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetVec3("dirlight.lightDir", dir);
	});
}

CGLDirctionLight::~CGLDirctionLight()
{
}
