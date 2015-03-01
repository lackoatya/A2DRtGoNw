#include <string>

#include "GLM\gtc\type_ptr.hpp"
#include "GLM\gtc\matrix_transform.hpp"

#include "P3A\Graphics\Test.h"

P3A::Graphics::Test::Test(P3A::Graphics::GraphicsContext & _context) :
	context(_context)
{
	meshes = new Engine::Graphics::Mesh*[1];
	meshes[0] = new Engine::Graphics::Mesh(std::string("P3A\\Data\\Meshes\\testxx.mesh"));

	appearances = new Engine::Graphics::Appearance*[1];
	appearances[0] = new Engine::Graphics::Appearance(std::string("P3A\\Data\\Appearances\\testxx.appearance"), std::string("P3A\\Data\\Textures"));

	model = new Model(meshes[0], appearances[0], 0, Vector2(0.f, 0.f), context);
}

P3A::Core::State P3A::Graphics::Test::Process(real32 const& _elapsed_time)
{
	context.PollEvents();

	Handle_Keys();
	Handle_Mouse();

	Update(_elapsed_time);
	Render();

	context.SwapBuffers();

	return P3A::Core::State(glfwWindowShouldClose(context.window) ? P3A::Core::CoreState::EXIT : P3A::Core::CoreState::CONTINUE);
}

void P3A::Graphics::Test::Update(real32 const& _elapsed_time)
{
	model->Update(_elapsed_time);
}

void P3A::Graphics::Test::Render()
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

	model->Render();

	glBindVertexArray(0);
}

void P3A::Graphics::Test::Handle_Keys(void)
{
	//if (glfwGetKey(context.window, GLFW_KEY_W) || glfwGetKey(context.window, GLFW_KEY_UP))
}

void P3A::Graphics::Test::Handle_Mouse(void)
{

}
