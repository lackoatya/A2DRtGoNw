#ifndef P3A_GRAPHICS_WORLD_RENDERER_H_
#define P3A_GRAPHICS_WORLD_RENDERER_H_

#include "Engine/Processor/NonDeterministicUpdater.hpp"
#include "Engine/Graphics/ModelBase.h"
#include "Engine/Graphics/Appearance.h"

#include "P3A/CoreResult.h"
#include "P3A/Game/World.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/Model.h"

namespace P3A {
namespace Graphics {
class WorldRenderer : public Engine::Processor::NonDeterministicProcessInterface<P3A::CoreResult> {
  public:
    WorldRenderer(P3A::Game::World * _world, P3A::Graphics::GraphicsContext * _graphics_context);
    inline WorldRenderer(void) = delete;
    inline virtual ~WorldRenderer(void) = default; // TODO this should be written!

    P3A::CoreResult Process(real32 const& _elapsed_time);

  private:
    P3A::Game::World * world_ = nullptr;
    P3A::Graphics::GraphicsContext * graphics_context_ = nullptr;

    bool clicked[2];
    Engine::Graphics::Mesh ** meshes_ = nullptr;
    Engine::Graphics::Appearance ** appearances_ = nullptr;

    P3A::Graphics::Model * model_ = nullptr;

    void Update(real32 const& _elapsed_time);
    void Render(void);

    void HandleKeys(void);
    void HandleMouse(void);
};
}
}

#endif