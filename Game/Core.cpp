#include "Engine\Physics\Reality.h"
#include "Engine\Core\Deterministic.hpp"

int main()
{
	Engine::Core::Deterministic< Engine::Physics::Reality >(1.0f / 60.0f);
	return 0;
}