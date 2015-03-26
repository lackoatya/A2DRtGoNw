#ifndef ENGINE_CORE_PROCESSABLE_H_
#define ENGINE_CORE_PROCESSABLE_H_

#include "Engine/Types.h"

namespace Engine {
namespace Core {
template <class ProcessResult>
class ProcessableInterface_Deterministic {
  public:
    virtual ProcessResult Process(void) = 0;
};

template <class ProcessResult>
class ProcessableInterface_NonDeterministic {
  public:
    virtual ProcessResult Process(real32 const& _elapsed_time) = 0;
};
}
}

#endif