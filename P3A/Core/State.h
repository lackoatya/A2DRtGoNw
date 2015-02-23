#pragma once

#include "Engine\Core\Result.h"

namespace P3A
{
	namespace Core
	{
		enum class CoreState
		{
			CONTINUE = 0,

			MENU,
			LOCAL,
			LOBBY,
			EXIT,

			Count
		};

		class State :
			public Engine::Core::ProcessResult < CoreState >
		{
		public:
			inline State(void) = delete;
			inline State(CoreState const& _result) : Engine::Core::ProcessResult< CoreState >(_result) { }
			inline State(State && _other) : Engine::Core::ProcessResult< CoreState >(_other) { }
			inline State(State const& _other) : Engine::Core::ProcessResult< CoreState >(_other) { }
			inline State & operator=(State const& _other) { Engine::Core::ProcessResult< CoreState >::operator=(_other); return *this; }
			inline ~State(void) = default;

			bool Valid(void) const { return result != CoreState::CONTINUE; }
		};
	}
}