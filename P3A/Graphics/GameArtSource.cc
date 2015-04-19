#include "P3A/Graphics/GameArtSource.h"

P3A::Graphics::GameArtSource::GameArtSource(void) {
  meshes_ = new Engine::Graphics::Mesh*[1];
  meshes_[0] = new Engine::Graphics::Mesh(std::string("P3A\\Data\\Meshes\\samurai.mesh"));

  appearances_ = new Engine::Graphics::Appearance*[1];
  appearances_[0] = new Engine::Graphics::Appearance(
    std::string("P3A\\Data\\Appearances\\samurai.appearance"), std::string("P3A\\Data\\Textures"));

  textures_ = new Engine::Graphics::TextureBase*[2];
  textures_[0] = new Engine::Graphics::TextureBase("P3A\\Data\\Textures\\tmp.png");
  textures_[1] = new Engine::Graphics::TextureBase("P3A\\Data\\Textures\\crypt_wall.png");
}

P3A::Graphics::GameArtSource::~GameArtSource(void) {

}