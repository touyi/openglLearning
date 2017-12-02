#pragma once
#include<string>
#include<SOIL\SOIL.h>
#include <GL\glew.h>
#include<GLM\glm.hpp>
#include<GLM\gtc\matrix_transform.hpp>
#include<GLM\gtc\type_ptr.hpp>
#include<map>
class CMShader
{
public:
	CMShader(std::string vshaderpath,std::string fshaderpath,std::string gshaderpath = "");
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
	void SetTexture(GLint textureNo, std::string path,int type = SOIL_LOAD_RGBA)
	{
		glActiveTexture(GL_TEXTURE0 + textureNo);
		auto it = textureMap.find(path);
		if (it != textureMap.end())
		{
			glBindTexture(GL_TEXTURE_2D, it->second);
		}
		else
		{
			GLuint id = LoadTexture(path.c_str(), type);
			textureMap[path] = id;
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	void LoadGeometryShader(const char* path);
private:
	unsigned int LoadTexture(const char*, int);
	bool iserror = false;
	GLuint m_program;
	std::map<std::string, GLuint>textureMap;
};

