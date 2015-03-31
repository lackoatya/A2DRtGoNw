#ifndef ENGINE_GRAPHICS_CAMERA_H
#define ENGINE_GRAPHICS_CAMERA_H

#include "GLM/glm.hpp"

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
class ContextBase;

class Camera : public NonCopyable {
  public:
    inline Camera(void) = default;
    inline virtual ~Camera(void) = default;

    void UpdateVectors(ContextBase const& _context, Vector2 const& _position);

    inline glm::vec3 center(void) const { return center_; }
    inline glm::vec3 eye(void) const { return eye_; }
    inline glm::vec3 up(void) const { return up_; }

  private:
    glm::vec3 center_ = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
};
}
}

#endif
