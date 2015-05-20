#ifndef LABYRINTH_MENU_RENDERER_H_
#define LABYRINTH_MENU_RENDERER_H_

// TODO Rossz kutya!!!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "Engine/Platform.h"
#include "Engine/Graphics/GL/Mesh.h"
#include "Engine/Graphics/GL/Shader.h"
#include "Engine/Graphics/GL/Texture.h"
#include "Engine/Updater/Deterministic.hpp"

#include "Labyrinth/CoreResult.h"
#include "Labyrinth/Graphics/IContext.h"

namespace Labyrinth {
namespace Menu {
class Renderer : public Engine::Updater::IDeterministicProcess < CoreResult > {
public:
  Renderer(real32 const& _interval, Graphics::IContext * _context);
  inline virtual ~Renderer(void) = default;

  CoreResult Process(void);

private:
  Engine::Graphics::GL::Mesh m_mesh;
  Engine::Graphics::GL::Shader m_shader;
  Engine::Graphics::GL::Texture m_texture;

  // TODO nagyon rossz itt!!!!!!!!4
  // glm::mat4 m_matWorld;
  // glm::mat4 m_matView;
  // glm::mat4 m_matProj;

  uint32 m_selected_option = 0;
  CoreResult m_result = CoreResult(CoreState::CONTINUE);

  Graphics::IContext * m_context = nullptr;

  void Render(void);

  void HandleKeys(void);
  void HandleMouse(void);
};
}
}

#endif