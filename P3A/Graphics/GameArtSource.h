#ifndef P3A_GRAPHICS_GAME_ART_SOURCE_H_
#define P3A_GRAPHICS_GAME_ART_SOURCE_H_

#include "Engine/Types.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/Appearance.h"
#include "Engine/Graphics/TextureBase.h"

namespace P3A {
namespace Graphics {
class GameArtSource : public NonCopyable {
  public:
    GameArtSource(void);
    virtual ~GameArtSource(void);

    // TODO Implement accessors!

    Engine::Graphics::Mesh ** meshes_ = nullptr;
    Engine::Graphics::Appearance ** appearances_ = nullptr;
    Engine::Graphics::TextureBase ** textures_ = nullptr;
};
}
}

#endif