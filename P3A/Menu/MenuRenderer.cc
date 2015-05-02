#include "P3A/Menu/MenuRenderer.h"

namespace P3A {
namespace Menu {
MenuRenderer::MenuRenderer(real32 const& _interval, Graphics::GraphicsContext * _context)
    : Engine::Updater::IDeterministicProcess < CoreResult >(_interval)
    , m_context(_context) {
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::UP, GLFW_KEY_W));
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::DOWN, GLFW_KEY_S));
  // bindings.state.push_back(Engine::Graphics::KeyHandler<Keys>::KeyBinding(Keys::ESCAPE, GLFW_KEY_ESCAPE));
}

CoreResult MenuRenderer::Process() {
  m_context->PollEvents();

  HandleKeys();
  HandleMouse();

  Render();


  return CoreResult(m_context->ShouldClose() ? CoreState::EXIT : m_result);
}

void MenuRenderer::HandleKeys(void) {
  if (m_context->GetKey(GLFW_KEY_W) || m_context->GetKey(GLFW_KEY_UP))
    m_selected_option = (0 < m_selected_option ? m_selected_option - 1 : 5 - 1);
  if (m_context->GetKey(GLFW_KEY_S) || m_context->GetKey(GLFW_KEY_DOWN))
    m_selected_option = (m_selected_option < 5 - 1 ? m_selected_option + 1 : 0);

  if (m_context->GetKey(GLFW_KEY_ENTER)) {
    switch (m_selected_option)
    {
    case 0: m_result = CoreState::SOLE; break;
    case 1: m_result = CoreState::CLIENT; break;
    case 2: m_result = CoreState::HOST; break;
    case 3: m_result = CoreState::OPTIONS; break;
    case 4: m_result = CoreState::EXIT; break;
    default: assert(false && "Unknown CoreState!");
    }
  }

  if (m_context->GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    m_context->Close();
}

void MenuRenderer::HandleMouse(void) {

}

void MenuRenderer::Render(void) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  static const float center_x = m_context->window_width() / 2.0f;
  static const float center_y = 200.f;

  m_context->PrepareStringDraw();

  m_context->DrawString(Graphics::Font::ARIAL_BLACK, ">> per Aspera ad Astra <<", center_x,
                      m_context->window_height() - 2 * 32.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);

  m_context->DrawString(Graphics::Font::ARIAL_BLACK, (m_selected_option == 0 ? ">Local Game" : "Local Game"),
                      center_x, center_y + 4 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);
  m_context->DrawString(Graphics::Font::ARIAL_BLACK, (m_selected_option == 1 ? ">Join Network Game" : "Join Network Game"),
                      center_x, center_y + 3 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);
  m_context->DrawString(Graphics::Font::ARIAL_BLACK, (m_selected_option == 2 ? ">Host Network Game" : "Host Network Game"),
                      center_x, center_y + 2 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);
  m_context->DrawString(Graphics::Font::ARIAL_BLACK, (m_selected_option == 3 ? ">Options" : "Options"),
                      center_x, center_y + 1 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);
  m_context->DrawString(Graphics::Font::ARIAL_BLACK, (m_selected_option == 4 ? ">Exit" : "Exit"),
                      center_x, center_y + 0 * 48.f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      Graphics::StringAlignment::MIDDLE);

  glBindVertexArray(0);

  m_context->SwapBuffers();
}
}
}
