#pragma once

#include "Engine\Types.h"

namespace Engine
{
	namespace Core
	{
		template < class ProcessResult >
		class Processable
		{
		public:
			// Constructor
			inline Processable(void) = default;
			// Copy Constructor
			inline Processable(Processable && _other) = delete;
			inline Processable(Processable const& _other) = delete;
			// Assignment operator
			inline Processable & operator=(Processable && _other) = delete;
			inline Processable & operator=(Processable const& _other) = delete;
			// Destructor
			inline virtual ~Processable(void) = default;

			virtual ProcessResult Process(real32 const& _elapsed_time) = 0;
		};
	}
}