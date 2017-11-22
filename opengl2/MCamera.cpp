#include "MCamera.h"



void CMCamera::Move(glm::vec3 dis)
{
	glm::vec3 right = glm::normalize(glm::cross(cameraUp, cameraFront));
	cameraPos += right*dis.x;
	cameraPos += glm::normalize(cameraFront)*dis.z;

}

void CMCamera::Rota(EulerAngle rota)
{
	cameraFront.z = -cos(glm::radians(rota.pitch)) * cos(glm::radians(rota.yaw));
	cameraFront.y = sin(glm::radians(rota.pitch));
	cameraFront.x = cos(glm::radians(rota.pitch)) * sin(glm::radians(rota.yaw));
}

glm::mat4 CMCamera::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

CMCamera::CMCamera():cameraPos(glm::vec3(0,0,0)),cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
}


CMCamera::~CMCamera()
{
}
