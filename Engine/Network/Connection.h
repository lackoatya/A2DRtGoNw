#ifndef ENGINE_NETWORK_CONNECTION_H_
#define ENGINE_NETWORK_CONNECTION_H_

#include <string>

#include "BOOST/asio.hpp"
#include "BOOST/thread.hpp"
#include "BOOST/atomic.hpp"

#include "Engine/Types.h"

namespace Engine {
namespace Network {
class Connection {
  public:
    explicit Connection(boost::asio::io_service & _io_service);
    inline Connection(void) = delete;
    inline Connection(Connection && _other) = delete;
    inline Connection(Connection const& _other) = delete;
    inline Connection & operator=(Connection && _other) = delete;
    inline Connection & operator=(Connection const& _other) = delete;
    virtual ~Connection(void);

    void Start(void);

    void TCP_Send(Packet const& _packet);
    void UDP_Send(Packet const& _packet);

    virtual void Process(char * _data, size_t const& _received) = 0;
    virtual void Dispose(void);

    inline boost::asio::ip::tcp::socket const& tcp_socket(void) const { return tcp_socket_; };
    inline boost::asio::ip::udp::socket const& udp_socket(void) const { return udp_socket_; };

  protected:
    atomic<bool> disposed_;

    char * tcp_data_ = nullptr, * udp_data_ = nullptr;
    boost::asio::ip::tcp::socket tcp_socket_;
    boost::asio::ip::udp::socket udp_socket_;

    void TCP_Receive(void);
    void UDP_Receive(void);

    void TCP_ReceiveCallback(boost::system::error_code const& _error, size_t const& _received);
    void UDP_ReceiveCallback(boost::system::error_code const& _error, size_t const& _received);

    void TCP_SendCallback(boost::system::error_code const& _error, size_t const& _sent);
    void UDP_SendCallback(boost::system::error_code const& _error, size_t const& _sent);
};
}
}

#endif