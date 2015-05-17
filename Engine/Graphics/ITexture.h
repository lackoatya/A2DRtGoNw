#ifndef ENGINE_GRAPHICS_ITEXTURE_H_
#define ENGINE_GRAPHICS_ITEXTURE_H_

#include "Engine/Types.h"

// TODO Nemyo

namespace Engine {
namespace Graphics {
class ITexture : public NonCopyable {
public:
  inline uint32 width(void) const { return m_width; }
  inline uint32 height(void) const { return m_height; }

protected:
  int32 m_width = 0, m_height = 0;
};
}
}

#endif