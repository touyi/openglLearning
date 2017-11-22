#pragma once
#include<GLM\glm.hpp>
#include<GLM\gtc\matrix_transform.hpp>
#include<GLM\gtc\type_ptr.hpp>
#include"mstd.h"
class CMCamera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
public:
	glm::vec3& GetPositon()
	{
		return cameraPos;
	}
	glm::vec3& GetFront()
	{
		return cameraFront;
	}
	void Move(glm::vec3 dis);
	void Rota(EulerAngle);
	glm::mat4 GetViewMatrix();
	CMCamera();
	~CMCamera();
};

