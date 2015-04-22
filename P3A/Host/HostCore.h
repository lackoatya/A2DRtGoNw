#ifndef P3A_HOST_HOST_CORE_H_
#define P3A_HOST_HOST_CORE_H_

#include "Engine/Types.h"
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
#include "P3A/Host/HostGame.h"
#include "P3A/Host/HostObserver.h"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
class HostCore : public NonCopyable {
  public:
    HostCore( Graphics::GraphicsContext * _context
            , Graphics::GameArtSource * _art_source );
    virtual ~HostCore(void);

    CoreResult Run(void);

  private:
    Graphics::GraphicsContext * m_context = nullptr;
    Graphics::GameArtSource * m_art_source = nullptr;

    class HostCoreLobby {

    } * host_core_lobby = nullptr;

    class HostCoreGame {
      private:
        typedef Engine::Updater::Deterministic < GameResult > GameUpdater;
        typedef Engine::Processor::ThreadedBlocked < GameUpdater, GameResult > GameProcessor;

        typedef Engine::Updater::NonDeterministic < CoreResult > RendererUpdater;
        typedef Engine::Processor::Blocked < RendererUpdater, CoreResult > RendererProcessor;

      public:
        HostCoreGame( Graphics::GraphicsContext * _context
                    , Graphics::GameArtSource * _art_source );
        virtual ~HostCoreGame(void);

      protected:
        Game::Hero * character = nullptr;

        Engine::Container::IntervalBuffer < HostSnapshot > * state_buffer_ = nullptr;

        HostGame * game_ = nullptr;
        GameUpdater game_updater_;
        GameProcessor game_processor_;

        HostObserver * renderer_ = nullptr;
        RendererUpdater renderer_updater_;
        RendererProcessor renderer_processor_;
    } * host_core_game = nullptr;
};
}
}

#endif