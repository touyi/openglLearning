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
	camera.Move(mov);
	camera.Rota(rotation);
}
GLfloat vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
int main()
{
	
	GLFWwindow* window = init(800,600,"learn",true);
	// 设置渲染窗口大小
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLfloat lasttime = glfwGetTime();
	GLfloat deltatime = 0;
	GLuint VBO,cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	CMCamera camera;
	glm::mat4 projection, view;
	auto cubeshader = CGLFactory::CreatShader("cubevshader.txt", "cubefshader.txt");
	cubeshader->SetTexture(0, "./res/container2.png");
	glEnable(GL_DEPTH_TEST);
	projection = glm::perspective(glm::radians(45.0f), width*1.0f / height, 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5, 0.5, 0.5, 0.5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		doMovement(camera, deltatime);
		glfwPollEvents();
		view = camera.GetViewMatrix();
		cubeshader->SetMat4("projection", projection);
		cubeshader->SetMat4("view", view);
		glm::mat4 model;
		cubeshader->SetMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(cubeVAO);
		

		CGLFactory::Update();

		deltatime = glfwGetTime() - lasttime;
		lasttime = glfwGetTime();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}




