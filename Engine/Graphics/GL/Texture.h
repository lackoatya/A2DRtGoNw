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
  inline Texture(const GLchar * _path);
  inline virtual ~Texture(void) {
    glDeleteTextures(1, &m_id);
  }

  GLuint operator()(void) const { return m_id; }

private:
  GLuint m_id = 0;
};
}
}
}

#endif