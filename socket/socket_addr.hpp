#ifndef SOCKET_ADDR_HPP
#define SOCKET_ADDR_HPP
#include "sock_base.hpp"

namespace net{
	::std::string sock_ntop(const sockaddr* sa, socklen_t addrlen);
	bool sock_cmp_addr(const sockaddr *sa1, const sockaddr *sa2);
}


#endif
