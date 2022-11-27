#ifndef SOCK_UTILS_HPP
#define SOCK_UTILS_HPP

#include "socket_port.hpp"
#include "socket_addr.hpp"

namespace net{
    int sockfd_to_family(int sockfd);
};


#endif
