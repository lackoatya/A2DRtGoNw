#ifndef ENGINE_NUMERICS_IINTERGRATOR_HPP_
#define ENGINE_NUMERICS_IINTERGRATOR_HPP_

namespace Engine {
namespace Numerics {
template < class State >
class IIntegrator {
public:
  virtual void Integrate(State const& _source, State * _target) = 0;
};
}
}

#endif