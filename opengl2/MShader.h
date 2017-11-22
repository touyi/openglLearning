#pragma once
#include<string>
#include <GL\glew.h>
#include<GLM\glm.hpp>
#include<GLM\gtc\matrix_transform.hpp>
#include<GLM\gtc\type_ptr.hpp>
class CMShader
{
public:
	CMShader(std::string vshaderpath,std::string fshaderpath);
	~CMShader();
	void use()
	{
		if (iserror)return;
		glUseProgram(m_program);
	}
	GLuint GetProgram()
	{
		return m_program;
	}
	GLint GetUniformLocation(std::string name)
	{
		return glGetUniformLocation(m_program, name.c_str());
	}
	GLint GetAttriLocation(std::string name)
	{
		return glGetAttribLocation(m_program, name.c_str());
	}
	void SetMat4(std::string name,glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void SetVec4(std::string name, glm::vec4 value)
	{
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
	}
	void SetVec3(std::string name, GLfloat x,GLfloat y,GLfloat z)
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}
	void SetVec3(std::string name, glm::vec3 value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}
	void SetMat3(std::string name, glm::mat3 value)
	{
		glUniformMatrix3fv(GetUniformLocation(name),1,GL_FALSE,glm::value_ptr(value));
	}
	void SetFloat(std::string name,GLfloat value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	void SetInt(std::string name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}
	void SetTexture(GLint textureNo, std::string path)
	{
		glActiveTexture(GL_TEXTURE0 + textureNo);
		glBindTexture(GL_TEXTURE_2D, LoadTexture(path.c_str()));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

private:
	unsigned int LoadTexture(const char*);
	bool iserror = false;
	GLuint m_program;
};

