#include "GLBaseLight.h"
#include"GLFactory.h"
#include"MShader.h"
CGLBaseLight::CGLBaseLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec,std::string lightName)
{
	ambient = amb;
	diffuse = diff;
	specular = spec;
	this->lightName = lightName;
	CGLFactory::GetInstance()->AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetVec3(lightName+".ambient", amb);
		sptr->SetVec3(lightName + ".diffuse", diff);
		sptr->SetVec3(lightName + ".specular", spec);
	});
}


CGLBaseLight::~CGLBaseLight()
{
}

void CGLBaseLight::SetVec3(glm::vec3 &value, std::string var)
{
	std::string light = lightName+".";
	CGLFactory::AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetVec3(light + var, value);
	});
}

void CGLBaseLight::SetFloat(float value, std::string var)
{
	std::string light = lightName + ".";
	CGLFactory::AddCallFunction([=](CGLFactory::ShaderPtr sptr) {
		sptr->SetFloat(light + var, value);
	});
}



