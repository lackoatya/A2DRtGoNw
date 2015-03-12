#include "P3A/Graphics/Menu.h"

namespace P3A {
namespace Graphics {
Menu::Menu(P3A::Graphics::GraphicsContext & _context)
    : context_(_context) {
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::UP, GLFW_KEY_W));
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::DOWN, GLFW_KEY_S));
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::ESCAPE, GLFW_KEY_ESCAPE));
}

P3A::Core::State P3A::Graphics::Menu::Process() {
  context_.PollEvents();

  HandleKeys();
  HandleMouse();

  Render();

  context_.SwapBuffers();

  return P3A::Core::State(context_.ShouldClose() ?
      P3A::Core::CoreState::EXIT : P3A::Core::CoreState::CONTINUE);
}

void Menu::HandleKeys(void) {
  if (context_.GetKey(GLFW_KEY_W) || context_.GetKey(GLFW_KEY_UP))
    selected_option_ = (0 < selected_option_ ? selected_option_ - 1 : 5 - 1);
  if (context_.GetKey(GLFW_KEY_S) || context_.GetKey(GLFW_KEY_DOWN))
    selected_option_ = (selected_option_ < 5 - 1 ? selected_option_ + 1 : 0);

  if (context_.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    context_.Close();
}

void P3A::Graphics::Menu::HandleMouse(void) {

}

void P3A::Graphics::Menu::Render(void)
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  static const float center_x = context_.window_width() / 2.0f;
  static const float center_y = 200.f;

  context_.PrepareStringDraw();

  context_.DrawString(Font::ARIAL_BLACK, ">> per Aspera ad Astra <<", center_x,
                      context_.window_height() - 2 * 32.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);

  context_.DrawString(Font::ARIAL_BLACK, (selected_option_ == 0 ? ">Local Game" : "Local Game"),
                      center_x, center_y + 4 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);
  context_.DrawString(Font::ARIAL_BLACK, (selected_option_ == 1 ? ">Join Network Game" : "Join Network Game"), 
                      center_x, center_y + 3 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);
  context_.DrawString(Font::ARIAL_BLACK, (selected_option_ == 2 ? ">Host Network Game" : "Host Network Game"), 
                      center_x, center_y + 2 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);
  context_.DrawString(Font::ARIAL_BLACK, (selected_option_ == 3 ? ">Options" : "Options"),
                      center_x, center_y + 1 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);
  context_.DrawString(Font::ARIAL_BLACK, (selected_option_ == 4 ? ">Exit" : "Exit"),
                      center_x, center_y + 0 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      StringAlignment::MIDDLE);

  glBindVertexArray(0);
}
}
}
