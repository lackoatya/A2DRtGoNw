#include "Labyrinth/Menu/Renderer.h"

namespace Labyrinth {
namespace Menu {
Renderer::Renderer(real32 const& _interval, Graphics::IContext * _context)
    : Engine::Updater::IDeterministicProcess < CoreResult >(_interval)
    , m_context(_context) {
  assert( _context );
}

CoreResult Renderer::Process() {
  m_context->PollEvents();

  HandleKeys();
  HandleMouse();

  Render();

  return CoreResult(m_context->ShouldClose() ? CoreState::EXIT : m_result);
}

void Renderer::HandleKeys(void) {
  if (m_context->GetKey(Engine::Graphics::VirtualKey::KEY_W))
    m_selected_option = (0 < m_selected_option ? m_selected_option - 1 : 5 - 1);
  if (m_context->GetKey(Engine::Graphics::VirtualKey::KEY_S))
    m_selected_option = (m_selected_option < 5 - 1 ? m_selected_option + 1 : 0);

  if (m_context->GetKey(Engine::Graphics::VirtualKey::KEY_ENTER)) {
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

  if (m_context->GetKey(Engine::Graphics::VirtualKey::KEY_ESCAPE))
    m_context->Close();
}

void Renderer::HandleMouse(void) {

}

void Renderer::Render(void) {
  m_context->Clear();

  static const float center_x = m_context->m_window_width / 2.f;
  static const float center_y = m_context->m_window_height / 2.f;

  // m_context->PrepareStringDraw();

  Graphics::Color color(1.0f, 0.0f, 1.0f, 1.0f);
  Graphics::StringAlignment alignment(Graphics::StringAlignment::MIDDLE);

  /*m_context->DrawString( Graphics::Font::ARIAL_BLACK, ">> per Aspera ad Astra <<"
                       , Vector2(center_x, center_y + 128.f), color, alignment);

  m_context->DrawString( Graphics::Font::ARIAL_BLACK, (m_selected_option == 0 ? ">Local Game" : "Local Game")
                       , Vector2(center_x, center_y + 2 * 48.f), color, alignment);
  m_context->DrawString( Graphics::Font::ARIAL_BLACK, (m_selected_option == 1 ? ">Join Network Game" : "Join Network Game")
                       , Vector2(center_x, center_y + 1 * 48.f), color, alignment);
  m_context->DrawString( Graphics::Font::ARIAL_BLACK, (m_selected_option == 2 ? ">Host Network Game" : "Host Network Game")
                       , Vector2(center_x, center_y + 0 * 48.f), color, alignment);
  m_context->DrawString( Graphics::Font::ARIAL_BLACK, (m_selected_option == 3 ? ">Options" : "Options")
                       , Vector2(center_x, center_y - 1 * 48.f), color, alignment);
  m_context->DrawString( Graphics::Font::ARIAL_BLACK, (m_selected_option == 4 ? ">Exit" : "Exit")
                       , Vector2(center_x, center_y - 2 * 48.f), color, alignment); */

  // glBindVertexArray(0);

  m_context->Present();
}
}
}
