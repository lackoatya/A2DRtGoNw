#ifndef ENGINE_NUMERICS_SYMPLECTIC_EULER_INTEGRATOR_HPP_
#define ENGINE_NUMERICS_SYMPLECTIC_EULER_INTEGRATOR_HPP_

#include "Engine/Numerics/IntegratorInterface.hpp"

namespace Engine {
namespace Numerics {
template <class State>
class SymplecticEulerIntegrator : public IntegratorInterface<State> {
  public:
    inline explicit SymplecticEulerIntegrator(real32 const& _dt) : dt_(_dt) { }
    inline virtual ~SymplecticEulerIntegrator(void) = default;

    void Integrate(State const& _source, State * _target) {
      _target->set_velocity(_source.velocity() + (_source.inverse_mass() * _source.force()) * dt_);
      _target->set_position(_source.position() + _target->velocity() * dt_);
    }

  private:
    real32 dt_ = 0.f;
};
}
}

#endif