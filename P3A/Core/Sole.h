#ifndef P3A_CORE_SOLE_H_
#define P3A_CORE_SOLE_H_

#include "Engine/Processor/DeterministicUpdater.hpp"
#include "Engine/Processor/NonDeterministicUpdater.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/ThreadedService.hpp"

#include "P3A/CoreResult.h"
#include "P3A/GameResult.h"
#include "P3A/Game/World.h"
#include "P3A/Graphics/WorldRenderer.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Core {
class Sole {
  private:
    typedef P3A::GameResult GameResult;
    typedef P3A::Game::World GameProcessable;
    typedef Engine::Processor::DeterministicUpdater<GameProcessable, GameResult> GameUpdater;
    typedef Engine::Processor::ThreadedService<GameUpdater, GameProcessable> GameProcessor;

    typedef P3A::CoreResult RendererResult;
    typedef P3A::Graphics::WorldRenderer RendererProcessable;
    typedef Engine::Processor::NonDeterministicUpdater<RendererProcessable, RendererResult>
        RendererUpdater;
    typedef Engine::Processor::Blocked<RendererUpdater, RendererProcessable, RendererResult>
        RendererProcessor;

  public:
    explicit Sole(P3A::Graphics::GraphicsContext * _context);
    virtual ~Sole(void);

    inline RendererResult Run(void) {
      game_processor_.Run();
      RendererResult result = renderer_processor_.Run();

      game_processor_.Stop();
      game_processor_.Join();

      return result;
    }

  private:
    GameProcessable * world_ = nullptr;
    GameUpdater game_updater_;
    GameProcessor game_processor_;

    RendererProcessable * renderer_ = nullptr;
    RendererUpdater renderer_updater_;
    RendererProcessor renderer_processor_;
};
}
}

#endif
