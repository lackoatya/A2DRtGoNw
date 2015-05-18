#ifndef ENGINE_GRAPHICS_IMESH_H_
#define ENGINE_GRAPHICS_IMESH_H_

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
class IMesh : public NonCopyable {
  virtual bool Load(const char * _path) = 0;
  virtual bool Release(void) = 0;
  virtual void Render(void) = 0;
};
}
}

#endif