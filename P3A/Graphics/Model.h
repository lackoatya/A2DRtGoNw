#ifndef P3A_GRAPHICS_MODEL_H_
#define P3A_GRAPHICS_MODEL_H_

#include "Engine/Graphics/ModelBase.h"

namespace P3A {
namespace Graphics {
class GraphicsContext;

class Model : public Engine::Graphics::ModelBase {
  public:
    inline Model(Engine::Graphics::Mesh * _mesh, Engine::Graphics::Appearance * _appearance,
                 uint32 const& _animation, Vector2 const& _location, GraphicsContext * _context)
        : ModelBase(_mesh, _appearance, _animation),
          location_(_location),
          context_(_context) { }
    inline Model(void) = delete;
    inline Model(Model && _other) = delete;
    inline Model(Model const& _other) = delete;
    inline Model & operator=(Model && _other) = delete;
    inline Model & operator=(Model const& _other) = delete;
    inline virtual ~Model(void) = default;

    void Render(void);

  private:
    Vector2 location_;
    GraphicsContext * context_ = nullptr;
  };
}
}

#endif