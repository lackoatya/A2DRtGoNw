#ifndef ENGINE_NUMERICS_SYMPLECTIC_EULER_INTEGRATOR_HPP_
#define ENGINE_NUMERICS_SYMPLECTIC_EULER_INTEGRATOR_HPP_

#include "Engine/Numerics/IIntegrator.hpp"

namespace Engine {
namespace Numerics {
template < class State >
class SymplecticEulerIntegrator : public IIntegrator < State > {
public:
  inline explicit SymplecticEulerIntegrator(real32 const& _dt)
      : m_dt(_dt) {
  }
  
  inline virtual ~SymplecticEulerIntegrator(void) {
  }

  void Integrate(State const& _source, State * _target) {
    _target->set_velocity(_source.velocity() + (_source.inverse_mass() * _source.force()) * m_dt);
    _target->set_position(_source.position() + _target->velocity() * m_dt);
  }

private:
  real32 m_dt = 0.f;
};
}
}

#endif