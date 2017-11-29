#include "MShader.h"
#include<fstream>
#include<iostream>
#include<sstream>
using std::fstream;
using std::stringstream;



CMShader::CMShader(std::string vshaderpath, std::string fshaderpath)
{
	fstream vfile;
	fstream sfile;
	
	vfile.exceptions(std::ifstream::badbit);
	sfile.exceptions(std::ifstream::badbit);
	try
	{
		vfile.open(vshaderpath);
		sfile.open(fshaderpath);
		stringstream vstr, fstr;
		vstr << vfile.rdbuf();
		fstr << sfile.rdbuf();
		
		GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
		// 坑点 不使用string 得到副本 而直接调用vstr.str().c_str() 返回的是临时的str 使用指针指向 会出错 应该拷贝一份
		std::string vs = vstr.str();
		std::string fs = fstr.str();
		const GLchar* vcode = vs.c_str();
		const GLchar* fcode = fs.c_str();

		glShaderSource(vshader, 1, &vcode, NULL);
		glShaderSource(fshader, 1, &fcode, NULL);
		// 编译
		glCompileShader(vshader);
		glCompileShader(fshader);

		GLint success = 0;
		glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[512];
			glGetShaderInfoLog(vshader, 512, NULL, infolog);
			//std::cout << infolog << std::endl;
			throw std::exception(infolog);
		}
		success = 0;
		glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[512];
			glGetShaderInfoLog(fshader, 512, NULL, infolog);
			//std::cout << infolog << std::endl;
			throw std::exception(infolog);
		}

		m_program = glCreateProgram();

		glAttachShader(m_program, vshader);
		glAttachShader(m_program, fshader);
		glLinkProgram(m_program);
		success = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);

		if (!success)
		{
			//std::cout << "link error!" << std::endl;
			throw std::exception("link error!");
		}
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		
	}
	catch (const std::exception& inf)
	{
		iserror = true;
		std::cout << inf.what() << std::endl;
		system("pause");
		exit(1);
		
		//std::cout << "file error!" << std::endl;
	}
	
}

CMShader::~CMShader()
{
}

unsigned int CMShader::LoadTexture(const char* path,int LoadType)
{
	int type;
	switch (LoadType)
	{
	case SOIL_LOAD_RGB:
		type = GL_RGB;
		break;
	case SOIL_LOAD_RGBA:
		type = GL_RGBA;
		break;
	default:
		type = GL_RGB;
		break;
	}
	int width, height, nrChannels;
	unsigned char *data = SOIL_load_image(path, &width, &height, 0, LoadType);//stbi_load(path, &width, &height, &nrChannels, 0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(data);
	return texture;
}
