#include "P3A\Graphics\Menu.h"

P3A::Graphics::Menu::Menu(P3A::Graphics::GraphicsContext & _context) :
	context(_context)
{
	bindings.state.push_back(Engine::Graphics::KeyHandler< Keys >::KeyBinding(Keys::UP,		GLFW_KEY_W));
	bindings.state.push_back(Engine::Graphics::KeyHandler< Keys >::KeyBinding(Keys::DOWN,	GLFW_KEY_S));
	bindings.state.push_back(Engine::Graphics::KeyHandler< Keys >::KeyBinding(Keys::ESCAPE, GLFW_KEY_ESCAPE));
}

P3A::Core::State P3A::Graphics::Menu::Process()
{
	context.PollEvents();

	Handle_Keys();
	Handle_Mouse();

	Render();

	context.SwapBuffers();

	return P3A::Core::State(glfwWindowShouldClose(context.window) ? P3A::Core::CoreState::EXIT : P3A::Core::CoreState::CONTINUE);
}

void P3A::Graphics::Menu::Handle_Keys(void)
{
	if (glfwGetKey(context.window, GLFW_KEY_W) || glfwGetKey(context.window, GLFW_KEY_UP))		current = (0 < current ? current - 1 : 5 - 1);
	if (glfwGetKey(context.window, GLFW_KEY_S) || glfwGetKey(context.window, GLFW_KEY_DOWN))	current = (current < 5 - 1 ? current + 1 : 0);

	if (glfwGetKey(context.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(context.window, true);
}

void P3A::Graphics::Menu::Handle_Mouse(void)
{

}

void P3A::Graphics::Menu::Render(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const float center_x = context.window_width / 2.0f;
	static const float center_y = 200.f;

	context.shader_text->Use();

	context.DrawString(context.font_arial_black, ">> per Aspera ad Astra <<", center_x, context.window_height - 2 * 32.0f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);

	context.DrawString(context.font_arial_black, (current == 0 ? ">Local Game" : "Local Game"), center_x, center_y + 4 * 48.f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);
	context.DrawString(context.font_arial_black, (current == 1 ? ">Join Network Game" : "Join Network Game"), center_x, center_y + 3 * 48.f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);
	context.DrawString(context.font_arial_black, (current == 2 ? ">Host Network Game" : "Host Network Game"), center_x, center_y + 2 * 48.f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);
	context.DrawString(context.font_arial_black, (current == 3 ? ">Options" : "Options"), center_x, center_y + 1 * 48.f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);
	context.DrawString(context.font_arial_black, (current == 4 ? ">Exit" : "Exit"), center_x, center_y + 0 * 48.f, P3A::Graphics::GraphicsContext::StringAlignment::MIDDLE);

	glBindVertexArray(0);
}
