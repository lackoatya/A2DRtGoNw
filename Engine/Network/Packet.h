#ifndef ENGINE_NETWORK_PACKET_H
#define ENGINE_NETWORK_PACKET_H

#include <string>

#include "Engine/Platform.h"

namespace Engine {
namespace Network {
struct Packet : public NonCopyable {
  public:
    uint32 size = 0;
    char * data = nullptr;

    Packet(const std::string &_message);
    ~Packet();

    static std::string ToString(char* _data, unsigned int _size);
};
}
}

#endif
