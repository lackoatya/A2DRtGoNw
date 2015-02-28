#pragma once

#include <string>

#include "Engine\Types.h"

// TODO Use boost's ptr_vector?

namespace Engine
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			class Element
			{
			public:
				class Joint
				{
				public:
					Vector2 owner_location, target_location;
					uint32 target_index = 0;

					// Joint * next = nullptr;

					// Constructor
					inline Joint(Vector2 && _owner_location, uint32 const& _target_index, Vector2 && _target_location/*, Joint * _next*/) :
						owner_location(std::move(_owner_location)),
						target_location(std::move(_target_location)),
						target_index(_target_index)/*,
						next(_next)*/ { }
					// Copy Constructor
					inline Joint(Joint && _other) = delete;
					inline Joint(Joint const& _other) = delete;
					// Assignment operator
					inline Joint & operator=(Joint && _other) = delete;
					inline Joint & operator=(Joint const& _other) = delete;
					// Destructor
					/*virtual ~Joint(void)
					{
						// delete next;
						next = nullptr;
					}*/
					inline virtual ~Joint(void) = default;
				};

			public:
				uint32 depth = 0;

				uint32 joints_count = 0;
				Joint ** joints = nullptr;

				// Constructor
				inline Element(uint32 const& _depth, uint32 const& _joints_count, Joint ** _joints) :
					depth(_depth),
					joints_count(_joints_count),
					joints(_joints) { }
				// Copy Constructor
				inline Element(Element && _other) = delete;
				inline Element(Element const& _other) = delete;
				// Assignment operator
				inline Element & operator=(Element && _other) = delete;
				inline Element & operator=(Element const& _other) = delete;
				// Destructor
				inline virtual ~Element(void)
				{
					for (uint32 current = 0; current < joints_count; ++current)
						delete joints[current];
					delete[] joints;
					joints = nullptr;
				}
			};

			class Animation
			{
			public:
				class Frame
				{
				public:
					class Transformation
					{
					public:
						uint32 index = 0;
						real32 rotation = 0.f;

						//Transformation * next = nullptr;

						// Constructor
						inline Transformation(void) = delete;
						inline Transformation(uint32 const& _index, real32 const& _rotation) : index(_index), rotation(_rotation) { }
						// Copy Constructor
						inline Transformation(Transformation && _other) = delete;
						inline Transformation(Transformation const& _other) = delete;
						// Assignment operator
						inline Transformation & operator=(Transformation && _other) = delete;
						inline Transformation & operator=(Transformation const& _other) = delete;
						// Destructor
						inline virtual ~Transformation(void) = default;
					};

				public:
					real32 end = 0.f;

					uint32 transformations_count = 0;
					Transformation ** transformations = nullptr;

					// Frame * next = nullptr;

					// Constructor
					inline Frame(void) = delete;
					inline Frame(real32 const& _end, uint32 const& _transformations_count, Transformation ** _transformations) :
						end(_end),
						transformations_count(_transformations_count),
						transformations(_transformations) { }
					// Copy Constructor
					inline Frame(Frame && _other) = delete;
					inline Frame(Frame const& _other) = delete;
					// Assignment operator
					inline Frame & operator=(Frame && _other) = delete;
					inline Frame & operator=(Frame const& _other) = delete;
					// Destructor
					inline virtual ~Frame(void)
					{
						for (uint32 current = 0; current < transformations_count; ++current)
							delete transformations[current];
						delete[] transformations;
						transformations = nullptr;
					}
				};

			public:
				uint32 frames_count = 0;
				Frame ** frames = nullptr;

				// Constructor
				inline Animation(void) = delete;
				inline Animation(uint32 const& _frames_count, Frame ** _frames) : frames_count(_frames_count), frames(_frames) { }
				// Copy Constructor
				inline Animation(Animation && _other) = delete;
				inline Animation(Animation const& _other) = delete;
				// Assignment operator
				inline Animation & operator=(Animation && _other) = delete;
				inline Animation & operator=(Animation const& _other) = delete;
				// Destructor
				inline virtual ~Animation(void)
				{
					for (uint32 current = 0; current < frames_count; ++current)
						delete frames[current];
					delete[] frames;
					frames = nullptr;
				}
			};

		public:
			uint32 elements_count = 0;
			Element ** elements = nullptr;

			uint32 animations_count = 0;
			Animation ** animations = nullptr;

			// Constructor
			Mesh(std::string && _mesh_path);
			// Copy Constructor
			inline Mesh(Mesh && _other) = delete;
			inline Mesh(Mesh const& _other) = delete;
			// Assignment operator
			inline Mesh & operator=(Mesh && _other) = delete;
			inline Mesh & operator=(Mesh const& _other) = delete;
			// Destructor
			inline virtual ~Mesh(void)
			{
				for (uint32 current = 0; current < elements_count; ++current)
					delete elements[current];
				delete[] elements;
				elements = nullptr;

				for (uint32 current = 0; current < animations_count; ++current)
					delete animations[current];
				delete[] animations;
				animations = nullptr;
			}
		};
	}
}
