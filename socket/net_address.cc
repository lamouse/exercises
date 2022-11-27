#include "net_address.hpp"
#include "socket_utils.hpp"

namespace net::ip{
    Address::Address(string ip, int port) noexcept :_port(port), _ip_addr(ip){
        
    }

    Address::Address(const Address& address)noexcept{
        _port = address._port;
        _ip_addr = address._ip_addr;
        _sa = address._sa;
        _pi = address._pi;
        _sa_len = address._sa_len;
    }

    Address::Address(const Address&& address)noexcept{
        _port = ::std::move(address._port);
        _ip_addr = ::std::move(address._ip_addr);
        _sa = ::std::move(address._sa);
        _pi = ::std::move(address._pi);
        _sa_len = ::std::move(address._sa_len);
    }

    Address::Address(const sockaddr& addr, const socklen_t len)noexcept : _sa_len(len){
        memcpy(&_sa, &addr, len);
        _port = get_sock_port(&addr);
        _ip_addr = sock_ntop(&addr, sizeof(addr));
    }

    Address::Address(const sockaddr& addr, const ProtocolInfo& proto, const socklen_t len) noexcept: _pi(proto), _sa_len(len){
        memcpy(&_sa, &addr, len);
        _port = get_sock_port(&addr);
        _ip_addr = sock_ntop(&addr, sizeof(addr));
    }

    Address::Address(string address) noexcept :_ip_addr(address){}
    int Address::port()const noexcept{
        return _port;
    }

    void Address::port(const int port) noexcept{
        _port = port;
    }

    ::std::string Address::ip_str() const noexcept {
        return _ip_addr;
    }

    sockaddr* Address::address()noexcept{
        return ((sockaddr*)&_sa);;
    }

    const sockaddr* Address::address()const noexcept{
        return ((const sockaddr *)&_sa);
    }
    Address Address::operator=(const Address& rhs){
        _port = rhs._port;
        _ip_addr = rhs._ip_addr;
        _sa = rhs._sa;
        _pi = rhs._pi;
        _sa_len = rhs._sa_len;
        return *this;
    }

    Address Address::operator=(const Address&& rhs){
        _port = ::std::move(rhs._port);
        _ip_addr = ::std::move(rhs._ip_addr);
        _sa = ::std::move(rhs._sa);
        _pi = ::std::move(rhs._pi);
        _sa_len = ::std::move(rhs._sa_len);
        return *this;
    }

    const ProtocolInfo& Address::protocol()const  noexcept{
        return _pi;
    }

    socklen_t& Address::sock_len()noexcept{
        return _sa_len;
    }

    const socklen_t& Address::sock_len()const noexcept{
        return _sa_len;
    }

};
