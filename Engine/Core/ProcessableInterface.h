#ifndef ENGINE_CORE_PROCESSABLE_H_
#define ENGINE_CORE_PROCESSABLE_H_

#include "Engine/Types.h"

namespace Engine {
namespace Core {
template <class ProcessResult>
class ProcessableInterface {
  public:
    inline ProcessableInterface(void) = default;
    inline ProcessableInterface(ProcessableInterface && _other) = delete;
    inline ProcessableInterface(ProcessableInterface const& _other) = delete;
    inline ProcessableInterface & operator=(ProcessableInterface && _other) = delete;
    inline ProcessableInterface & operator=(ProcessableInterface const& _other) = delete;
    inline virtual ~ProcessableInterface(void) = default;

    virtual ProcessResult Process(real32 const& _elapsed_time) = 0;
};
}
}

#endif