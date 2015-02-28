#include <fstream>

#include "Engine\Graphics\Appearance.h"

Engine::Graphics::Appearance::Appearance(std::string && _appearance_path, std::string && _texture_directory)
{
	std::ifstream file(_appearance_path);
	file >> element_textures_count;

	element_textures = new Texture_Base *[element_textures_count];
	for (uint32 current = 0; current < element_textures_count; ++current)
	{
		std::string texture_name; file >> texture_name;
		element_textures[current] = new Texture_Base((_texture_directory + "\\" + texture_name).c_str());
	}

	file.close();
}

Engine::Graphics::Appearance::~Appearance(void)
{
	for (uint32 current = 0; current < element_textures_count; ++current)
		delete element_textures[current];
	delete[] element_textures;
	element_textures = nullptr;
}
