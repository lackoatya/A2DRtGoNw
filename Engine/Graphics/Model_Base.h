#pragma once

#include "Engine\Types.h"
#include "Engine\Graphics\Mesh.h"
#include "Engine\Graphics\Appearance.h"

namespace Engine
{
	namespace Graphics
	{
		class Model_Base
		{
		public:
			class Interpolation_Base
			{
			public:
				real32 time = 0.f;

				uint32 rotations_count = 0;
				real32 * rotations = nullptr;

				// Constructor
				inline Interpolation_Base(void) = delete;
				inline Interpolation_Base(real32 const& _time, uint32 const& _rotations_count) :
					time(_time),
					rotations_count(_rotations_count)
				{
					rotations = new real32[rotations_count];
					memset(rotations, 0.f, rotations_count * sizeof(real32));
				}
				// Copy Constructor
				inline Interpolation_Base(Interpolation_Base && _other) = delete;
				inline Interpolation_Base(Interpolation_Base const& _other) = delete;
				// Assignment operator
				inline Interpolation_Base & operator=(Interpolation_Base && _other) = delete;
				inline Interpolation_Base & operator=(Interpolation_Base const& _other) = delete;
				// Destructor
				inline virtual ~Interpolation_Base(void) { delete[] rotations; }
			};

		public:
			Mesh * mesh = nullptr;
			Appearance * appearance = nullptr;

			uint32 frame, animation = 0;

			Interpolation_Base * interpolation_current = nullptr, * interpolation_start = nullptr, * interpolation_end = nullptr;

			// Constructor
			inline Model_Base(void) = delete;
			inline Model_Base(Engine::Graphics::Mesh * _mesh, Engine::Graphics::Appearance * _appearance, uint32 const& _animation) :
				mesh(_mesh),
				appearance(_appearance),
				animation(_animation)
			{ 
				interpolation_start = new Interpolation_Base(0.f, _mesh->elements_count);
				interpolation_current = new Interpolation_Base(0.f, _mesh->elements_count);
				interpolation_end = new Interpolation_Base(0.f, _mesh->elements_count);

				SetFrame(0);
			}
			// Copy Constructor
			inline Model_Base(Model_Base && _other) = delete;
			inline Model_Base(Model_Base const& _other) = delete;
			// Assignment operator
			inline Model_Base & operator=(Model_Base && _other) = delete;
			inline Model_Base & operator=(Model_Base const& _other) = delete;
			// Destructor
			inline virtual ~Model_Base(void)
			{
				delete interpolation_start;
				delete interpolation_current;
				delete interpolation_end;
			}

			virtual void Animate(uint32 const& _animation);
			virtual void Update(real32 const& _elapsed_time);

			virtual void Render(void) = 0;
		protected:
			virtual void SetFrame(uint32 const& _frame);
		};
	}
}