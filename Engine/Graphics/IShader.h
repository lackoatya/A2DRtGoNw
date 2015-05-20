#ifndef ENGINE_GRAPHICS_ISHADER_H_
#define ENGINE_GRAPHICS_ISHADER_H_

#include "Engine/Platform.h"

namespace Engine {
namespace Graphics {
class IShader : public NonCopyable {
public:
  virtual bool Load( std::string const& _vertex_path
                   , std::string const& _fragment_path ) = 0;
  virtual bool Release(void) = 0;
};
}
}

#endif