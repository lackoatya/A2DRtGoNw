#ifndef ENGINE_GRAPHICS_GL_TEXTURE_H_
#define ENGINE_GRAPHICS_GL_TEXTURE_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "Engine/Types.h"
#include "Engine/Graphics/ITexture.h"

namespace Engine {
namespace Graphics {
namespace GL {
class Texture : public ITexture {
public:
  inline Texture(void) {
  }
  
  inline virtual ~Texture(void) {
    Release();
  }

  bool Load(const char * _path);
  inline bool Release(void) {
    bool expected = true;
    if (m_loaded.compare_exchange_strong(expected, false))
      glDeleteTextures(1, &m_id);
    return expected;
  }

  GLuint operator()(void) const { return m_id; }

private:
  GLuint m_id = 0;
};
}
}
}

#endif