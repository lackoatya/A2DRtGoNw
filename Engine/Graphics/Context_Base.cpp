#include <assert.h>

#include "GLM\gtc\matrix_transform.hpp"

#include "Engine\Graphics\Context_Base.h"

Engine::Graphics::Context_Base::Context_Base(uint32 const& _window_width, uint32 const& _window_height, real32 _camera_min_distance, real32 _camera_max_distance) :
	window_width(_window_width),
	window_height(_window_height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	assert(window = glfwCreateWindow(window_width, window_height, "Game", nullptr, nullptr));
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, window_width, window_height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	projectionMatrix = glm::mat4();
	projectionMatrix = glm::ortho(0.0f, (float)window_width, 0.0f, (float)window_height, _camera_min_distance, _camera_max_distance);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Engine::Graphics::Context_Base::~Context_Base(void)
{
	glfwTerminate();

	// TODO other stuff DUDE LOL WTF?!
}