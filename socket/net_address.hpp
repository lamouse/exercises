#ifndef NET_ADDRESS_HPP
#define NET_ADDRESS_HPP
#include "sock_base.hpp"

namespace net :: ip{

    struct ProtocolInfo{
        int family;
        int type;
        int protocol;
    };

    class Address{
        private:
            using string = ::std::string;
            int _port;
            string _ip_addr;
            sockaddr_storage _sa;
            ProtocolInfo _pi;
            socklen_t _sa_len;
        public:
            Address()=default;
            Address(string ip, int port) noexcept;
            Address(string ip) noexcept;
            Address(const sockaddr& addr, const socklen_t len) noexcept;
            Address(const sockaddr& addr, const ProtocolInfo& proto, const socklen_t len) noexcept;
            Address(const Address& address) noexcept;
            Address(const Address&& address) noexcept;
            int port() const noexcept;
            void port(const int port) noexcept;
            string ip_str() const noexcept;
            Address operator=(const Address& rhs);
            Address operator=(const Address&& rhs);
            sockaddr* address() noexcept;
            const sockaddr* address()const noexcept;
            const ProtocolInfo& protocol()const  noexcept;
            socklen_t& sock_len() noexcept;
            const socklen_t& sock_len() const noexcept;
    };
};



#endif