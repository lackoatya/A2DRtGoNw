#include "Engine/Utility/Logger.h"

#include <stdio.h>      /* fopen, fputs, fclose, stderr */
#include <stdlib.h>     /* abort, NULL */
#include <string>

namespace Engine {
namespace Utility {
  void AbortWithMessage(char const* _message) {
    fputs(_message, stderr);
    abort();
  }

  void AbortWithMessageAndData(char const* _message, char const* _data) {
    char concatenated_message[512] = { '\0' };
    strcpy_s(concatenated_message, _message);
    strcat_s(concatenated_message, _data);
    fputs(concatenated_message, stderr);
    abort();
  }

  // TODO
  void ReportAssert(const char* _condition, const char* _file, int _line, const char* _message) {
    /*fputs("%s(%d): Assert Failure: ", file, line);

    if (_condition != NULL) std::printf("'%s' ", condition);
    if (msg != NULL) std::printf("%s", msg);

    std::printf("\n");*/
  }
}
}