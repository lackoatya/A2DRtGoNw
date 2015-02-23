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
			inline Processable(void) = default;
			inline Processable(const Processable &_other) = default;
			inline Processable & operator=(const Processable &_other) = default;
			inline virtual ~Processable(void) = default;

			virtual ProcessResult Process() = 0;
		};
	}
}