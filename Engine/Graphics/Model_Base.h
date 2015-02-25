#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Engine\Types.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture_Base;

		class Element_Base
		{
		public:
			struct Joint_Base
			{
			public:
				Vector2 owner_location, target_location;
				Element_Base * target;

				inline Joint_Base(void) = delete;
				inline Joint_Base(Vector2 && _owner_location, Element_Base * _target, Vector2 && _target_location) : owner_location(_owner_location), target(_target), target_location(_target_location) { }
				inline Joint_Base(Joint_Base && _other) : owner_location(std::move(_other.owner_location)), target_location(std::move(_other.target_location)), target(std::move(_other.target)) { }
				inline Joint_Base(Joint_Base const& _other) : owner_location(_other.owner_location), target_location(_other.target_location), target(_other.target) { }
				inline Joint_Base & operator=(Joint_Base && _other) = delete;
				inline Joint_Base & operator=(Joint_Base const& _other) = delete;
				inline virtual ~Joint_Base(void) = default;
			};

		public:
			uint32 index = 0, depth = 0;
			Texture_Base * texture = nullptr;

			real32 rotation = 0.f;

			std::vector< Joint_Base * > joints;

			inline Element_Base(void) = delete;
			Element_Base(uint8 const& _index, uint8 const& _depth, std::string const& _texture_path);
			inline Element_Base(Element_Base const& _other) = delete;
			inline Element_Base(Element_Base && _other) : index(_other.index), depth(_other.depth), texture(_other.texture), rotation(_other.rotation), joints(_other.joints) { }
			inline Element_Base & operator=(Element_Base const& _other) = delete;
			inline virtual ~Element_Base(void) = default;
		};

		class Animation_Base
		{
		public:
			class Frame_Base
			{
			public:
				class Frame_Transformation
				{
				public:
					uint32 index = 0;
					real32 rotation = 0.f;

					inline Frame_Transformation(void) = default;
					inline Frame_Transformation(uint8 const& _index, real32 const& _rotation) : index(_index), rotation(_rotation) { }
					inline Frame_Transformation(Frame_Transformation const& _other) : index(_other.index), rotation(_other.rotation) { }
					inline Frame_Transformation(Frame_Transformation && _other) : index(_other.index), rotation(_other.rotation) { }
					inline Frame_Transformation & operator=(Frame_Transformation const& _other) = delete;
					inline virtual ~Frame_Transformation(void) = default;
				};

			public:
				real32 duration = 0.f;
				std::vector< Frame_Transformation * > transformations;

				inline Frame_Base(void) = delete;
				inline Frame_Base(real32 const& _duration) : duration(_duration) { }
				inline Frame_Base(Frame_Base const& _other) : duration(_other.duration), transformations(_other.transformations) { }
				inline Frame_Base(Frame_Base && _other) : duration(_other.duration), transformations(_other.transformations) { }
				inline Frame_Base & operator=(Frame_Base const& _other) = delete;
				inline virtual ~Frame_Base(void) = default;
			};

		public:
			std::vector< Frame_Base * > frames;

			inline Animation_Base(void) = default;
			inline Animation_Base(Animation_Base const& _other) : frames(_other.frames) { }
			inline Animation_Base(Animation_Base && _other) : frames(_other.frames) { }
			inline Animation_Base & operator=(Animation_Base const& _other) = delete;
			inline virtual ~Animation_Base(void) = default;
		};

		class Model_Base
		{
		public:
			real32 elapsed_time = 0.f;
			Vector2 location = Vector2(0.f, 0.f);

			Element_Base * main_element = nullptr;
			std::vector< Element_Base * > elements;
			Animation_Base * animation = nullptr;
			std::vector< Animation_Base * > animations;

			inline Model_Base(void) = delete;
			Model_Base(std::string const& _path, std::string const& _name, Vector2 const& _location);
			inline Model_Base(Model_Base const& _other) = delete;
			inline Model_Base & operator=(Model_Base const& _other) = delete;
			virtual ~Model_Base(void);
		};
	}
}