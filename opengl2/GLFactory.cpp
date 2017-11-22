#include "GLFactory.h"
#include"GLPointLight.h"
#include"GLDirctionLight.h"
#include"GLSpotLight.h"
CGLFactory* CGLFactory::instance;
std::list<CGLFactory::ShaderPtr> CGLFactory::ShaderList;
std::vector<std::function<void(CGLFactory::ShaderPtr)>> CGLFactory::callBackFuns;
std::list<CGLFactory::LightPtr> CGLFactory::LightList;

CGLFactory* CGLFactory::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CGLFactory();
	}
	return instance;
}
CGLFactory::CGLFactory()
{
}


CGLFactory::~CGLFactory()
{
}

void CGLFactory::AddCallFunction(std::function<void(ShaderPtr)> fun)
{
	callBackFuns.push_back(fun);
}

void CGLFactory::Update()
{
	for (auto it2 = ShaderList.begin(); it2 != ShaderList.end(); it2++)
	{
		(*it2)->use();
		for (auto it = callBackFuns.begin(); it != callBackFuns.end(); it++)
		{
			(*it)(*it2);
		}
	}
	callBackFuns.clear();
}

CGLFactory::ShaderPtr CGLFactory::CreatShader(std::string vpath, std::string fpath)
{
	ShaderPtr sp = ShaderPtr(new CMShader(vpath, fpath));
	ShaderList.push_back(sp);
	return sp;
}

CGLFactory::LightPtr CGLFactory::CreatPointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic)
{
	// 点光源
	LightPtr lptr = LightPtr(new CGLPointLight(amb, diff, spec, constant, linear, quadratic));
	LightList.push_back(lptr);
	return lptr;
}

CGLFactory::LightPtr CGLFactory::CreatSpotLight(glm::vec3 SpotDir, float cutoff, float outercutOff, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
{
	// 光源集合
	LightPtr lptr(new CGLSpotLight(SpotDir, cutoff, outercutOff, amb, diff, spec));
	LightList.push_back(lptr);
	return lptr;
}

CGLFactory::LightPtr CGLFactory::CreatDirctionLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir)
{
	
	// 光源集合
	LightPtr lptr(new CGLDirctionLight(amb, diff, spec, dir));
	LightList.push_back(lptr);
	return lptr;
}
