#pragma once

//#include "GLEW\glew.h"
#include "GLM\glm.hpp"
//#include "GLM\gtc\matrix_transform.hpp"

#include "Engine\Types.h"

namespace Engine
{
	namespace Graphics
	{
		class Context_Base;

		class Camera
		{
		public:
			glm::vec3 center = glm::vec3(0.0f, 0.0f, 2.0f);
			glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

			inline Camera(void) = default;
			inline Camera(Camera const& _other) = delete;
			inline Camera & operator=(Camera const& _other) = delete;
			inline virtual ~Camera(void) = default;

			void UpdateVectors(Context_Base const& _context, Vector2 const& _position);
		};
	}
}
