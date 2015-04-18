#ifndef P3A_SOLE_SOLE_CORE_H_
#define P3A_SOLE_SOLE_CORE_H_

#include "Engine/Container/Buffer.hpp"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Processor/DeterministicUpdater.hpp"
#include "Engine/Processor/NonDeterministicUpdater.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/Threaded.hpp"

#include "P3A/CoreResult.h"
#include "P3A/GameResult.h"
#include "P3A/Game/HeroBase.h"
#include "P3A/Game/Configuration.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"
#include "P3A/Sole/SoleGame.h"
#include "P3A/Sole/SoleObserver.h"
#include "P3A/Sole/SoleSnapshot.h"

namespace P3A {
namespace Sole {
class SoleCore : public NonCopyable {
  private:
    typedef GameResult GameResult;
    typedef SoleGame GameProcessable;
    typedef Engine::Processor::DeterministicUpdater<GameProcessable, GameResult> GameUpdater;
    typedef Engine::Processor::Threaded<GameUpdater, GameProcessable, GameResult> GameProcessor;

    typedef CoreResult RendererResult;
    typedef SoleObserver RendererProcessable;
    typedef Engine::Processor::NonDeterministicUpdater<RendererProcessable, RendererResult>
        RendererUpdater;
    typedef Engine::Processor::Blocked<RendererUpdater, RendererProcessable, RendererResult>
        RendererProcessor;

  public:
    Game::Configuration configuration_;

    explicit SoleCore(P3A::Graphics::GraphicsContext * _context,
                      P3A::Graphics::GameArtSource * _art_source);
    virtual ~SoleCore(void);

    CoreResult Run(void);

  private:
    Game::Hero * character = nullptr;

    Engine::Container::IntervalBuffer<SoleSnapshot> * state_buffer_ = nullptr;

    GameProcessable * game_ = nullptr;
    GameUpdater game_updater_;
    GameProcessor game_processor_;

    RendererProcessable * renderer_ = nullptr;
    RendererUpdater renderer_updater_;
    RendererProcessor renderer_processor_;


    // Mind....
};
}
}

#endif
