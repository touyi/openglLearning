#include"mstd.h"
#include"MShader.h"
#include"MCamera.h"
#include"GLFactory.h"
#include"GLBaseLight.h"
GLboolean keyState[1025] = {false};
GLfloat aspect = 45;
EulerAngle rotation;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
	{
		keyState[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyState[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLdouble sensitivity = 0.1;
	static GLdouble lastx, lasty;
	static GLboolean isfir = true;
	if (isfir)
	{
		isfir = false;
		lastx = xpos;
		lasty = ypos;
	}
	else
	{
		GLdouble offsetx = xpos - lastx;
		GLdouble offsety = lasty - ypos;
		lastx = xpos;
		lasty = ypos;
		rotation.pitch += offsety*sensitivity;
		rotation.yaw += offsetx*sensitivity;
		if (rotation.pitch > 89)rotation.pitch = 89;
		if (rotation.pitch < -89)rotation.pitch = -89;
	}
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	aspect -= yoffset;
	if (aspect <= 1.0f)
		aspect = 1.0f;
	if (aspect >= 45.0f)
		aspect = 45.0f;
}
GLFWwindow* init(GLint width,GLint height, char* wname,GLboolean isDisableCursor = false)
{
	glfwInit(); // 初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, wname, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "打开窗口失败" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// 绑定窗口
	glfwMakeContextCurrent(window);
	if(isDisableCursor)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 将该项设置为true可以使glew管理函数指针使用现代方法，如果把它设置为GL_FALSE的话可能会在使用OpenGL的核心模式时出现一些问题。
	glewExperimental = GL_TRUE;
	// 初始化函数指针
	glewInit();
	return window;
}
void doMovement(CMCamera& camera, GLfloat deltatime)
{
	GLfloat speed = 5.0f;
	glm::vec3 mov(0, 0, 0);
	float dis = speed * deltatime;
	if (keyState[GLFW_KEY_W])
	{
		mov.z += dis;
	}
	if (keyState[GLFW_KEY_S])
	{
		mov.z -= dis;
	}
	if (keyState[GLFW_KEY_A])
	{
		mov.x += dis;
	}
	if (keyState[GLFW_KEY_D])
	{
		mov.x -= dis;
	}
	if (keyState[GLFW_KEY_Q])
	{
		mov.y += dis;
	}
	if (keyState[GLFW_KEY_E])
	{
		mov.y -= dis;
	}
	camera.Move(mov);
	camera.Rota(rotation);
}
GLfloat vertices[] = {
	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
									  // Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};
float Planes[] = {
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};
glm::vec3 cubePositions[] = {
   glm::vec3(0.0f,  0.0f,  0.0f),
   glm::vec3(0.0f,0.0f,-5.0f),
};
float quadVertices[] = {
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};
GLuint GenSkyBox()
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	char *paths[7] = {
		"res/skybox/right.jpg",
		"res/skybox/left.jpg",
		"res/skybox/top.jpg",
		"res/skybox/bottom.jpg",
		"res/skybox/back.jpg",
		"res/skybox/front.jpg"
	};
	for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X; i < GL_TEXTURE_CUBE_MAP_POSITIVE_X + 6; i++)
	{
		int w, h,channels;
		unsigned char* data = SOIL_load_image(paths[i- GL_TEXTURE_CUBE_MAP_POSITIVE_X], &w, &h, &channels, SOIL_LOAD_RGB);
		glTexImage2D(i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		SOIL_free_image_data(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return tex;
}
int main()
{
	
	GLFWwindow* window = init(800,600,"learn",true);
	// 设置渲染窗口大小
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	GLuint SkyVAO, SkyVBO;
	glGenVertexArrays(1,&SkyVAO);
	glGenBuffers(1,&SkyVBO);
	glBindVertexArray(SkyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, SkyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	GLfloat lasttime = glfwGetTime();
	GLfloat deltatime = 0;
	CMCamera camera;
	glm::mat4 projection, view;
	
	
	projection = glm::perspective(glm::radians(45.0f), width*1.0f / height, 0.1f, 100.0f);
	auto shader = CGLFactory::CreatShader("vframe.txt", "fframe.txt","gshader.txt");
	//GLuint tex = GenSkyBox();
	
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		doMovement(camera,deltatime);
		glm::mat4 model;
		shader->use();
		glEnable(GL_PROGRAM_POINT_SIZE);
		shader->SetMat4("projection", projection);
		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_POINTS, 0, 3);
		glBindVertexArray(0);
		CGLFactory::Update();
		deltatime = glfwGetTime() - lasttime;
		lasttime = glfwGetTime();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}




