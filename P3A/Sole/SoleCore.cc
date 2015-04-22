#include "P3A/Sole/SoleCore.h"

namespace P3A {
namespace Sole {
SoleCore::SoleCore( Graphics::GraphicsContext * _context
                  , Graphics::GameArtSource * _art_source) 
    : character(new Game::Hero(0))

    , state_buffer_(new Engine::Container::IntervalBuffer < SoleSnapshot >(64, 1.f / 30.f))

    , game_(new SoleGame(state_buffer_, character))
    , game_updater_(game_)
    , game_processor_(&game_updater_)

    , renderer_(new SoleObserver(1.f / 60.f, character, _context, _art_source, state_buffer_))
    , renderer_updater_(renderer_)
    , renderer_processor_(&renderer_updater_) {
}

CoreResult SoleCore::Run(void) {
  game_processor_.Run();
  boost::this_thread::sleep_for(boost::chrono::milliseconds(static_cast<uint32>(state_buffer_->interval() * 4 * 1000)));
  CoreResult result = renderer_processor_.Run();

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
