#pragma once
#include"MShader.h"
#include<memory>
#include<string>
#include<list>
#include<functional>
#include<vector>
class CGLBaseLight;
// ��ʱ��֧�ֵ����Ͷ��Դ
class CGLFactory
{
public:
	static CGLFactory* instance;
	static CGLFactory* GetInstance();
	enum LightType
	{
		FA_DIR_LIGHT,
		FA_POINT_LIGHT,
		FA_SPOTLIGHT_LIGHT
	};
	typedef std::shared_ptr<CMShader> ShaderPtr;
	typedef std::shared_ptr<CGLBaseLight> LightPtr;
	CGLFactory();
	~CGLFactory();
	static void AddCallFunction(std::function<void(ShaderPtr)>fun);
	static void Update(); // ���¹�Դ
	// shader
	static ShaderPtr CreatShader(std::string vpath, std::string fpath,std::string gpath="");
	
	// ��Դ
	static LightPtr CreatPointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic);
	static LightPtr CreatSpotLight(glm::vec3 SpotDir, float cutoff, float outercutOff, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);
	static LightPtr CreatDirctionLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir);
	// ��ֹ��������ֵ
	CGLBaseLight& operator=(const CGLBaseLight&) = delete;
	CGLFactory(const CGLFactory&) = delete;

	// ���ٷ���
private:

	static std::list<ShaderPtr> ShaderList;
	static std::vector<std::function<void(ShaderPtr)>> callBackFuns;
	static std::list<LightPtr> LightList;
};



