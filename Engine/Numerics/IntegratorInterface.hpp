#ifndef ENGINE_NUMERICS_INTERGRATOR_INTERFACE_HPP_
#define ENGINE_NUMERICS_INTERGRATOR_INTERFACE_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Numerics {
template <class State>
class IntegratorInterface : public NonCopyable {
  public:
    virtual void Integrate(State const& _source, State * _target) = 0;

  protected:
    inline IntegratorInterface(void) = default;
    inline virtual ~IntegratorInterface(void) = default;
};
}
}

#endif