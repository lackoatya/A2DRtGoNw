#pragma once

#include <string>

#include "Engine\Types.h"
#include "Engine\Graphics\Texture_Base.h"

namespace Engine
{
	namespace Graphics
	{
		class Appearance
		{
		public:
			uint32 element_textures_count = 0;
			Texture_Base ** element_textures = nullptr;

			// Constructor
			inline Appearance(void) = delete;
			Appearance(std::string && _appearance_path, std::string && _texture_directory);
			// Copy Constructor
			inline Appearance(Appearance && _other) = delete;
			inline Appearance(Appearance const& _other) = delete;
			// Assignment operator
			inline Appearance & operator=(Appearance && _other) = delete;
			inline Appearance & operator=(Appearance const& _other) = delete;
			// Destructor
			virtual ~Appearance(void);
		};
	}
}
