#ifndef ENGINE_NETWORK_COMMAND_HANDLER_INTERFACE_H_
#define ENGINE_NETWORK_COMMAND_HANDLER_INTERFACE_H_

namespace Engine {
namespace Network {
class CommandHandlerInterface {
  public:
    virtual void Handle_TCP(char const* _data, size_t _received) = 0;
    virtual void Handle_UDP(char const* _data, size_t _received) = 0;

  protected:
    inline CommandHandlerInterface(void) = default;
    inline virtual ~CommandHandlerInterface(void) = default;
};
}
}

#endif