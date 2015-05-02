#ifndef P3A_HOST_HOST_CORE_CONFIGURATOR_H_
#define P3A_HOST_HOST_CORE_CONFIGURATOR_H_

#include "Engine/Types.h"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Processor/IResult.hpp"

namespace P3A {
namespace Host {
enum class ConfiguratorState {
  CONTINUE = 0,

  BINDED,
  ESCAPE,

  Count
};

class ConfiguratorResult : public Engine::Processor::IResult < ConfiguratorState > {
public:
  inline ConfiguratorResult(void)
    : Engine::Processor::IResult < ConfiguratorState >(ConfiguratorState::CONTINUE) {
  }
  inline ConfiguratorResult(ConfiguratorState const& _result)
    : Engine::Processor::IResult < ConfiguratorState >(_result) {
  }

  bool IsValid(void) const { return result() != ConfiguratorState::CONTINUE; }
  // LobbyState NotValid(void) const { return LobbyState::CONTINUE; }
};

class Core_Configurator : public Engine::Updater::IUpdatable < ConfiguratorResult > {
public:
  Core_Configurator(void);
  ~Core_Configurator(void);

  ConfiguratorResult Update(void);

private:
  enum class State {
    GETTING_IP,

    BINDING,
    BINDING_ERROR,
    BINDING_SUCCESS,
  } m_state = State::GETTING_IP;

  std::string m_address;
  std::string m_port;

  boost::system::error_code m_bind_result;

  void Render(void);
  void HandleInput(void);
};
}
}
#endif