#ifndef ENGINE_UTILITY_LOGGER_H_
#define ENGINE_UTILITY_LOGGER_H_

namespace Engine {
namespace Utility{
  void AbortWithMessage(char const* _message);
  void AbortWithMessageAndData(char const* _message, char const* _data);
}
}
#endif