#ifndef ENGINE_PROCESSOR_UPDATER_INTERFACE_HPP_
#define ENGINE_PROCESSOR_UPDATER_INTERFACE_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Processor {
template<class Processable, class Result>
class UpdaterInterface : public NonCopyable {
  public:
    virtual Result Update(void) = 0;

  protected:
    Processable * instance_ = nullptr;

    real32 elapsed_time_ = 0.f;
    boost::chrono::steady_clock::time_point last_time_ = boost::chrono::steady_clock::now();

    inline UpdaterInterface(Processable * _instance) : instance_(_instance) { }
    inline virtual ~UpdaterInterface(void) = default;

    void UpdateTime(void) {
      boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
      boost::chrono::duration<real32> difference = now - last_time_;
      elapsed_time_ += difference.count();
      last_time_ = now;
    }
};
}
}

#endif