/*#ifndef P3A_HOST_HOST_LOBBY_OBSERVER_H_
#define P3A_HOST_HOST_LOBBY_OBSERVER_H_

#include "Engine/Types.h"
#include "Engine/Updater/NonDeterministic.hpp"

#include "P3A/CoreResult.h" 

namespace P3A {
namespace Host {
enum class LobbyState {
  CONTINUE = 0,

  READY,
  SHUTDOWN,
  EXIT,

  Count
};

class LobbyResult : public Engine::Processor::ResultInterface < LobbyState > {
  public:
  inline LobbyResult(void)
    : Engine::Processor::ResultInterface < LobbyState >(LobbyState::CONTINUE) { }
  inline LobbyResult(LobbyState const& _result)
    : Engine::Processor::ResultInterface < LobbyState >(_result) { }
  inline LobbyResult(LobbyResult && _other)
    : Engine::Processor::ResultInterface < LobbyState >(_other) { }
  inline LobbyResult(LobbyResult const& _other)
    : Engine::Processor::ResultInterface < LobbyState >(_other) { }
  inline LobbyResult & operator=(LobbyResult && _other) {
    Engine::Processor::ResultInterface < LobbyState >::operator=(_other);
    return *this;
  }
  inline LobbyResult & operator=(LobbyResult const& _other) {
    Engine::Processor::ResultInterface < LobbyState >::operator=(_other);
    return *this;
  }
  inline ~LobbyResult(void) = default;

  bool IsValid(void) const { return result() != LobbyState::CONTINUE; }
  LobbyState NotValid(void) const { return LobbyState::CONTINUE; }
};

class HostLobbyObserver : public NonCopyable,
                          public Engine::Updater::NonDeterministicProcessInterface < LobbyResult > {

};
}
}*/

#endif