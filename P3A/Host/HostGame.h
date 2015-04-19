#ifndef P3A_HOST_HOST_GAME_H_
#define P3A_HOST_HOST_GAME_H_

#include "Engine/Numerics/SymplecticEulerIntegrator.hpp"

#include "P3A/GameResult.h"
#include "P3A/Game/HeroBase.h"
#include "P3A/Game/GameInterface.hpp"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
typedef HostSnapshot Snapshot;

class HostGame : public Game::GameInterface < Snapshot, GameResult > {
  public:
    inline HostGame(Engine::Container::IntervalBuffer < Snapshot > * _state_buffer
                    , Game::Hero * _character)
                    : Game::GameInterface < Snapshot, GameResult >(_state_buffer)
                    , character_(_character)
                    , integrator_(_state_buffer->interval()) {
      assert(_state_buffer);
      assert(_character);
    }
    inline virtual ~HostGame(void) = default;

  protected:
    uint32 last_character_input = 0;
    Game::Hero * character_ = nullptr;

    // TODO This should be a template parameter!
    Engine::Numerics::SymplecticEulerIntegrator < Engine::Physics::Body < Engine::Physics::AABB > > integrator_;

    void Process_Inputs(void);
    void Process_Hero_Input(Game::HeroState * _current, const Game::HeroInput * _input);

    void Process_States(void);
    void Process_Hero_State(const Game::HeroState * _current, Game::HeroState * _next);

    inline GameResult GetResult(void) { return GameState::CONTINUE; }
};
}
}

#endif