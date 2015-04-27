/*
#ifndef P3A_SOLE_SOLE_CORE_H_
#define P3A_SOLE_SOLE_CORE_H_

#include "Engine/Container/Buffer.hpp"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/ThreadedBlocked.hpp"

#include "P3A/CoreResult.h"
#include "P3A/GameResult.h"
#include "P3A/Game/HeroBase.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"
#include "P3A/Sole/SoleGame.h"
#include "P3A/Sole/SoleObserver.h"
#include "P3A/Sole/SoleSnapshot.h"

namespace P3A {
namespace Sole {
class SoleCore : public NonCopyable {
  private:
    typedef Engine::Updater::Deterministic < GameResult > GameUpdater;
    typedef Engine::Processor::ThreadedBlocked < GameUpdater, GameResult > GameProcessor;

    typedef Engine::Updater::NonDeterministic < CoreResult > RendererUpdater;
    typedef Engine::Processor::Blocked < RendererUpdater, CoreResult > RendererProcessor;

  public:
    explicit SoleCore( Graphics::GraphicsContext * _context
                     , Graphics::GameArtSource * _art_source );
    virtual ~SoleCore(void);

    CoreResult Run(void);

  private:
    Game::Hero * character = nullptr;

    Engine::Container::IntervalBuffer < SoleSnapshot > * state_buffer_ = nullptr;

    SoleGame * game_ = nullptr;
    GameUpdater game_updater_;
    GameProcessor game_processor_;

    SoleObserver * renderer_ = nullptr;
    RendererUpdater renderer_updater_;
    RendererProcessor renderer_processor_;


    // Mind....
};
}
}

#endif*/
