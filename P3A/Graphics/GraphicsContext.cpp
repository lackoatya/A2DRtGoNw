#include "GLM\glm.hpp"
#include "GLM\gtc\matrix_transform.hpp"
#include "GLM\gtc\type_ptr.hpp"

#include "P3A\Graphics\GraphicsContext.h"

P3A::Graphics::GraphicsContext::GraphicsContext(uint32 const& _window_width, uint32 const& _window_height, real32 _camera_min_distance, real32 _camera_max_distance) :
	Engine::Graphics::WindowContext(_window_width, _window_height, _camera_min_distance, _camera_max_distance)
{
	shader_text = new Engine::Graphics::Shader("P3A\\Shaders\\Text.vs", "P3A\\Shaders\\Text.frag");
	// TODO other shaders?

	font_arial_black = new Engine::Graphics::Texture("P3A\\Data\\Fonts\\arial_black.png");
}

void P3A::Graphics::GraphicsContext::DrawString(Engine::Graphics::Texture const* _font_texture, std::string const& _text, float const& _x, float const& _y, StringAlignment const& _alignment)
{
	static const unsigned int glyph_count = 16;

	glBindTexture(GL_TEXTURE_2D, _font_texture->textureID);

	GLint modelLoc = glGetUniformLocation(shader_text->shaderProgram, "model");
	projLoc = glGetUniformLocation(shader_text->shaderProgram, "projection");
	viewLoc = glGetUniformLocation(shader_text->shaderProgram, "view");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));


	float glyph_Width = (float)_font_texture->width / glyph_count;
	float glyph_Height = (float)_font_texture->height / glyph_count;
	float glyph_WidthRatio = 1.0 / glyph_count;
	float glyph_HeightRatio = 1.0 / glyph_count;

	float calculated_x = _x;
	switch (_alignment)
	{
	case StringAlignment::LEFT: break;
	case StringAlignment::MIDDLE: calculated_x -= (_text.length() * glyph_Width) / 2.0f; break;
	case StringAlignment::RIGHT: calculated_x -= _text.length() * glyph_Width; break;
	}

	for (unsigned int current = 0; current < _text.length(); current++)
	{
		float glyph_x = (float)(_text[current] % glyph_count);
		float glyph_y = (float)glyph_count - _text[current] / glyph_count - 1;

		glm::mat4 modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3(calculated_x + glyph_Width * current, _y, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		struct GlyphShape
		{
		public:
			GLfloat vertices[28];
			GLuint indices[6];
		} glyph;

		// TOP RIGHT:
		// Position Coords:
		glyph.vertices[0] = glyph_Width;
		glyph.vertices[1] = glyph_Height;

		// Colors:
		glyph.vertices[2] = 1.0f;
		glyph.vertices[3] = 0.0f;
		glyph.vertices[4] = 0.0f;

		// Texture Coords:
		glyph.vertices[5] = (glyph_x + 1) * glyph_WidthRatio;
		glyph.vertices[6] = (glyph_y + 1) * glyph_HeightRatio;
		// ----------------------------

		// BOTTOM RIGHT:
		// Position Coords:
		glyph.vertices[7] = glyph_Width;
		glyph.vertices[8] = 0.0f;

		// Colors:
		glyph.vertices[9] = 0.0f;
		glyph.vertices[10] = 1.0f;
		glyph.vertices[11] = 0.0f;

		// Texture Coords:
		glyph.vertices[12] = (glyph_x + 1) * glyph_WidthRatio;
		glyph.vertices[13] = (glyph_y + 0) * glyph_HeightRatio;
		// ----------------------------

		// BOTTOM LEFT:
		// Position Coords:
		glyph.vertices[14] = 0.0f;
		glyph.vertices[15] = 0.0f;

		// Colors:
		glyph.vertices[16] = 0.0f;
		glyph.vertices[17] = 0.0f;
		glyph.vertices[18] = 1.0f;

		// Texture Coords:
		glyph.vertices[19] = (glyph_x + 0) * glyph_WidthRatio;
		glyph.vertices[20] = (glyph_y + 0) * glyph_HeightRatio;
		// ----------------------------

		// TOP LEFT:
		// Position Coords:
		glyph.vertices[21] = 0.0f;
		glyph.vertices[22] = glyph_Height;

		// Colors:
		glyph.vertices[23] = 1.0f;
		glyph.vertices[24] = 1.0f;
		glyph.vertices[25] = 0.0f;

		// Texture Coords:
		glyph.vertices[26] = (glyph_x + 0) * glyph_WidthRatio;
		glyph.vertices[27] = (glyph_y + 1) * glyph_HeightRatio;
		// ----------------------------

		glyph.indices[0] = 0;
		glyph.indices[1] = 1;
		glyph.indices[2] = 3;
		glyph.indices[3] = 1;
		glyph.indices[4] = 2;
		glyph.indices[5] = 3;


		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glyph.vertices), glyph.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glyph.indices), glyph.indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}


P3A::Graphics::GraphicsContext::~GraphicsContext(void)
{

}