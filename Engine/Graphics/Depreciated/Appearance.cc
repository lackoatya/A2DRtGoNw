#include "Engine/Graphics/Appearance.h"

#include <fstream>

namespace Engine {
namespace Graphics {
Appearance::Appearance(std::string const& _appearance_path, std::string const& _texture_directory) {
  std::ifstream file(_appearance_path);
  assert(!file.fail() && "Error while opening appearance!");

  file >> element_textures_count_;
  element_textures_ = new TextureBase *[element_textures_count_];

  for (uint32 current = 0; current < element_textures_count_; ++current) {
    std::string texture_name; file >> texture_name;
    std::string texture_path = _texture_directory + "\\" + texture_name;
    element_textures_[current] = new TextureBase(texture_path.c_str());
  }

  file.close();
}

Appearance::~Appearance(void)
{
  for (uint32 current = 0; current < element_textures_count_; ++current)
    delete element_textures_[current];
  delete[] element_textures_;
  element_textures_ = nullptr;
}
}
}

