#ifndef ENGINE_NUMERICS_RUNGE_KUTTA_4_INTEGRATOR_HPP_
#define ENGINE_NUMERICS_RUNGE_KUTTA_4_INTEGRATOR_HPP_

#include "Engine/Platform.h"
#include "Engine/Numerics/IntegratorInterface.hpp"

namespace Engine {
namespace Numerics {
template <class State>
class RungeKutta4Integrator : public IntegratorInterface<State> {
  public:
    struct RungeKutta4StateDerivate {
      public:
        Vector2 velocity, acceleration;

    };

  public:
    inline RungeKutta4Integrator(real32 const& _dt) : dt_(_dt) { }
    inline RungeKutta4Integrator(void) = default;

    void Integrate(const State * _source, State * _target);

  protected:
    real32 dt_;
};
}
}

#endif