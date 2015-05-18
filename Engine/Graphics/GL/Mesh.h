#ifndef ENGINE_GRAPHICS_GL_MESH_H_
#define ENGINE_GRAPHICS_GL_MESH_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "Engine/Types.h"
#include "Engine/Graphics/IMesh.h"

namespace Engine {
namespace Graphics {
namespace GL {
class Mesh : public IMesh {
public:
  inline Mesh(void) {
  }

  virtual ~Mesh(void) {
    // TODO release
  }

  bool Load(const char * _path);
  bool Release(void);
  void Render(void);

private:
  uint32 m_triangles_count = 0;
  GLuint m_VAO = 0;
  GLuint m_VBO = 0;
  GLuint m_IBO = 0;
};
}
}
}

#endif