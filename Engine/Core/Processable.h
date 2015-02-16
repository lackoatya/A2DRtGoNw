#pragma once

#include "Engine\Types.h"

namespace Engine
{
	namespace Core
	{
		class Processable
		{
		public:
			Processable() = default;
			~Processable() = default;
			Processable(const Processable &_other) = default;
			Processable & operator=(const Processable &_other) = default;

			virtual uint8 Valid() = 0;  // TODO move this to StateHandler!
			virtual void Process() = 0;
		};
	}
}