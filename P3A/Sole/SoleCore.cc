#include "P3A/Sole/SoleCore.h"

namespace P3A {
namespace Sole {
SoleCore::SoleCore(Graphics::GraphicsContext * _context, Graphics::GameArtSource * _art_source)
    : configuration_(1, 16, 16 + 1, 1.f / 60.f)
    
    , character(new Game::Hero(0))

    , state_buffer_(new Engine::Container::IntervalBuffer<SoleSnapshot>(64, configuration_.interval()))

    , game_(new GameProcessable(configuration_.interval(), state_buffer_, character))
    , game_updater_(game_)
    , game_processor_(&game_updater_)

    , renderer_(new RendererProcessable(1.f / 60.f, character, _context, _art_source, state_buffer_))
    , renderer_updater_(renderer_)
    , renderer_processor_(&renderer_updater_) {
}

CoreResult SoleCore::Run(void) {
  game_processor_.Run();
  boost::this_thread::sleep_for(boost::chrono::milliseconds(static_cast<uint32>(configuration_.interval() * 4 * 1000)));
  RendererResult result = renderer_processor_.Run();

  game_processor_.Stop();
  game_processor_.Join();

  return result;
}

SoleCore::~SoleCore(void) {
  delete game_;
  game_ = nullptr;

  delete renderer_;
  renderer_ = nullptr;
}
}
}
