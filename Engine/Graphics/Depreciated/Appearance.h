#ifndef ENGINE_GRAPHICS_APPEARANCE_H_
#define ENGINE_GRAPHICS_APPEARANCE_H_

#include <string>

#include "Engine/Types.h"
#include "Engine/Graphics/TextureBase.h"

namespace Engine {
namespace Graphics {
class Appearance : public NonCopyable {
  public:
    Appearance(std::string const& _appearance_path, std::string const& _texture_directory);
    virtual ~Appearance(void);

    inline uint32 element_textures_count(void) const { return element_textures_count_; }
    inline TextureBase ** element_textures(void) const { return element_textures_; }

  private:
    uint32 element_textures_count_ = 0;
    TextureBase ** element_textures_ = nullptr;
};
}
}

#endif
