#include "P3A/Core/Sole.h"

P3A::Core::Sole::Sole(P3A::Graphics::GraphicsContext * _graphics)
    : world_(new P3A::Game::World()),
      game_updater_(world_, 1.f / 30.f),
      game_processor_(&game_updater_),

      renderer_(new P3A::Graphics::WorldRenderer(world_, _graphics)),
      renderer_updater_(renderer_, 1.f / 60.f),
      renderer_processor_(&renderer_updater_) {
}

P3A::Core::Sole::~Sole(void) {
  delete world_;
  world_ = nullptr;

  delete renderer_;
  renderer_ = nullptr;
}
