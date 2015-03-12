#ifndef ENGINE_CORE_LOGGER_H_
#define ENGINE_CORE_LOGGER_H_

namespace Engine {
namespace Core{
  void AbortWithMessage(char const* _message);
  void AbortWithMessageAndData(char const* _message, char const* _data);
}
}
#endif