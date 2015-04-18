#ifndef ENGINE_UTILITY_LOGGER_H_
#define ENGINE_UTILITY_LOGGER_H_

namespace Engine {
namespace Utility{
  void AbortWithMessage(char const* _message);
  void AbortWithMessageAndData(char const* _message, char const* _data);
  void ReportAssert(const char* _condition, const char* _file, int _line, const char* _message);
}
}
/*
#define UTILITY_HALT() __debugbreak()
#define UTILITY_UNUSED(x) do { (void)sizeof(x); } while(0)

#ifdef UTILITY_ASSERT_ENABLED
#define UTILITY_ASSERT(cond) \
  do { \
    if (!(cond)) { \
      Engine::Utility::ReportAssert(#cond, __FILE__, __LINE__, 0) \
      UTILITY_HALT(); \
      } \
  } while(0)
#else
#define UTILITY_ASSERT(condition) do { UTILITY_UNUSED(condition); } while(0)
#endif
  */
#endif