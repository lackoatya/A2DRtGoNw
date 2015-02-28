#pragma once

// GLEW
#define GLEW_STATIC
#include "GLEW\glew.h"

// GLFW
#include "GLFW\glfw3.h"

#define OPENGL_MAJOR_VERSION	3
#define OPENGL_MINOR_VERSION	3

#include "GLM\glm.hpp"

#include "Engine\Types.h"
#include "Engine\Graphics\Camera.h"

namespace Engine
{
	namespace Graphics
	{
		class Context_Base
		{
		public:
			inline Context_Base(void) = delete;
			Context_Base(uint32 const& _window_width, uint32 const& _window_height, real32 _camera_min_distance = 0.01f, real32 _camera_max_distance = 64.f);
			inline Context_Base(Context_Base const& _other) = delete;
			inline Context_Base & operator=(Context_Base const& _other) = delete;
			virtual ~Context_Base(void);

			//inline GLFWwindow * Window(void) const { return window; }
			inline void PollEvents(void) const { glfwPollEvents(); }
			inline void SwapBuffers(void) const { glfwSwapBuffers(window); }
			inline void SetUserPointer(void * _pointer) const { glfwSetWindowUserPointer(window, _pointer); }

		//private:
			GLuint VAO;
			GLuint VBO;
			GLuint EBO;

			GLint viewLoc;
			glm::mat4 viewMatrix;
			GLint projLoc;
			glm::mat4 projectionMatrix;

			Camera camera;

			uint32 window_width, window_height;
			GLFWwindow *window;
		};
	}
}

/*namespace StringAlignment
{
	enum Type
	{
		LEFT,
		MIDDLE,
		RIGHT
	};
};
void DrawString(const Texture *_font_texture, const std::string &_text, const float &_x, const float &_y, const StringAlignment::Type &_alignment);
void DrawTexture(const Texture *_texture, const float &_x, const float &_y, const float &_width, const float &_height);*/