#include "P3A/Host/HostCore.h"

#include "BOOST/lexical_cast.hpp"

namespace P3A {
namespace Host {
HostCore::HostCore( Graphics::GraphicsContext * _context
                  , Graphics::GameArtSource * _art_source)
    : m_context(_context)
    , m_art_source(_art_source)

    , m_service()
    , m_gateway(Engine::Network::Gateway::Configuration(3, 1425), &m_service) {
}


CoreResult HostCore::Run(void) {
  /*Render();
  HandleInput();

  if (m_state == State::BINDING) {
    address ip_address(address::from_string(m_address));
    uint32 port(boost::lexical_cast < uint32 >(m_port));
    m_bind_result = m_gateway.Bind(tcp_endpoint(ip_address, port));

    if (m_bind_result) m_state = State::BINDING_ERROR;
    else m_state = State::BINDING_SUCCESS;
  }*/

  return CoreState::MENU;
}

HostCore::~HostCore(void) {
}
}
}