#include "Labyrinth/Menu/Renderer.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace Labyrinth {
namespace Menu {
Renderer::Renderer(real32 const& _interval, Graphics::IContext * _context)
    : Engine::Updater::IDeterministicProcess < CoreResult >(_interval)
    , m_context(_context) {
  assert( _context );

  assert( m_mesh.Load("Data\\Meshes\\Hero.mesh") );
  assert( m_shader.Load("Data\\Shaders\\Hero.vs", "Data\\Shaders\\Hero.frag") );
  assert( m_texture.Load("Data\\Textures\\Hero.png") );

  glEnable(GL_CULL_FACE); // kapcsoljuk be a hatrafele nezo lapok eldobasat
  glEnable(GL_DEPTH_TEST); // mélységi teszt bekapcsolása (takarás)
  glCullFace(GL_BACK); // GL_BACK: a kamerától "elfelé" nézõ lapok, GL_FRONT: a kamera felé nézõ lapok

  // m_matProj = glm::ortho(0.0f, static_cast<real32>(m_context->m_window_width), 0.0f,
  //                             static_cast<real32>(m_context->m_window_height), 0.01f, 64.0f);

  glViewport(0, 0, 800, 600);
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
  // m_matView = glm::lookAt(glm::vec3(0, 0, -10),		// honnan nézzük a színteret
  //                         glm::vec3(0, 0, 0),		// a színtér melyik pontját nézzük
  //                         glm::vec3(0, 1, 0));		// felfelé mutató irány a világban
}

void Renderer::Render(void) {
  m_context->Clear();

  static const float center_x = m_context->m_window_width / 2.f;
  static const float center_y = m_context->m_window_height / 2.f;

  // a mesh kirajzolasahoz hasznalt shader bekapcsolasa
  glUseProgram(m_shader());

  // glBindTexture(GL_TEXTURE_2D, m_texture());

  /*glm::mat4 modelMatrix = glm::mat4(1.f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, -10.0f)) *
                glm::rotate(modelMatrix, 0.f, glm::vec3(0.f, 0.f, 1.f));


  m_matWorld = glm::mat4(1.0f); 
  glm::mat4 mvp = m_matProj * m_matView * m_matWorld;
  glUniformMatrix4fv(m_shader["MVP"], 1, GL_FALSE, glm::value_ptr(mvp));

  // glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture());
  glUniform1i(m_shader["texture"], 0);*/

  m_mesh.Render();

  glUseProgram(0);


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
