#include "GLM\gtc\type_ptr.hpp"
#include "GLM\gtc\matrix_transform.hpp"

#include "P3A\Graphics\Test.h"

P3A::Graphics::Test::Test(P3A::Graphics::GraphicsContext & _context) :
context(_context)
{
	model = new Model("P3A\\Data\\Models", "testxx", Vector2(0.f, 0.f));
}

P3A::Core::State P3A::Graphics::Test::Process()
{
	context.PollEvents();

	Handle_Keys();
	Handle_Mouse();

	Render();

	context.SwapBuffers();

	return P3A::Core::State(glfwWindowShouldClose(context.window) ? P3A::Core::CoreState::EXIT : P3A::Core::CoreState::CONTINUE);
}

void P3A::Graphics::Test::Handle_Keys(void)
{
	//if (glfwGetKey(context.window, GLFW_KEY_W) || glfwGetKey(context.window, GLFW_KEY_UP))
}

void P3A::Graphics::Test::Handle_Mouse(void)
{

}

void P3A::Graphics::Test::Render(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	context.camera.UpdateVectors(context, Vector2(0.f, 0.f));
	context.viewMatrix = glm::lookAt(context.camera.center, context.camera.eye, context.camera.up);

	context.shader_box->Use();

	context.viewLoc = glGetUniformLocation(context.shader_box->shaderProgram, "view");
	context.projLoc = glGetUniformLocation(context.shader_box->shaderProgram, "projection");

	glUniformMatrix4fv(context.viewLoc, 1, GL_FALSE, glm::value_ptr(context.viewMatrix));
	glUniformMatrix4fv(context.projLoc, 1, GL_FALSE, glm::value_ptr(context.projectionMatrix));

	model->Render(context);

	glBindVertexArray(0);
}
