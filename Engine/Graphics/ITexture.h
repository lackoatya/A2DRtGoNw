#ifndef ENGINE_GRAPHICS_ITEXTURE_H_
#define ENGINE_GRAPHICS_ITEXTURE_H_

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
class ITexture : public NonCopyable {
public:
  virtual bool Load(const char * _path) = 0;
  virtual bool Release(void) = 0;

  inline bool IsLoaded(void) const { return m_loaded.load(); }
  inline uint32 width(void) const {return m_width; }
  inline uint32 height(void) const { return m_height; }

protected:
  ITexture(void)
      : m_loaded(false) {
  }

  inline virtual ~ITexture(void) = default;

  atomic < bool > m_loaded;
  int32 m_width = 0, m_height = 0;
};
}
}

#endif