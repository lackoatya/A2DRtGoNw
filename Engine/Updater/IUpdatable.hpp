#ifndef ENGINE_UPDATER_IUPDATABLE_HPP_
#define ENGINE_UPDATER_IUPDATABLE_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Updater {
template < class Result >
class IUpdatable : public NonCopyable {
public:
  virtual Result Update(void) = 0;
};
}
}

#endif