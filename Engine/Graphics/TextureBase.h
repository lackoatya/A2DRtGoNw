#ifndef ENGINE_GRAPHICS_TEXTUREBASE_H_
#define ENGINE_GRAPHICS_TEXTUREBASE_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
  class TextureBase {
  public:
    explicit TextureBase(const GLchar * _path);
    inline TextureBase(void) = delete;
    inline TextureBase(TextureBase && _other) = delete;
    inline TextureBase(TextureBase const& _other) = delete;
    inline TextureBase & operator=(TextureBase && _other) = delete;
    inline TextureBase & operator=(TextureBase const& _other) = delete;
    inline virtual ~TextureBase(void) { glDeleteTextures(1, &id_); }

    void Render(Vector2 const& _center, real32 const& _rotation);

    inline GLuint id(void) const { return id_; }
    inline uint32 width(void) const { return width_; }
    inline uint32 height(void) const { return height_; }

  private:
    GLuint id_ = 0;
    int32 width_ = 0, height_ = 0;
};
}
}

#endif