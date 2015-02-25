#include "Engine\Graphics\Camera.h"
#include "Engine\Graphics\Context_Base.h"

void Engine::Graphics::Camera::UpdateVectors(Context_Base const& _context, Vector2 const& _position)
{
	real32 x = _position.x - _context.window_width / 2.0f, y = _position.y - _context.window_height / 2.0f;

	center = glm::vec3(x, y, 1.0f);
	eye = glm::vec3(x, y, 0.0f);
}