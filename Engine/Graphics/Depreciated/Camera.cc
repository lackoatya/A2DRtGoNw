#include "Engine/Graphics/Camera.h"

#include "Engine/Graphics/ContextBase.h"

namespace Engine {
namespace Graphics {
void Camera::UpdateVectors(ContextBase const& _context, Vector2 const& _position) {
  real32 x = _position.x - _context.window_width() / 2.0f;
  real32 y = _position.y - _context.window_height() / 2.0f;

  center_ = glm::vec3(x, y, 1.0f);
  eye_ = glm::vec3(x, y, 0.0f);
}
}
}