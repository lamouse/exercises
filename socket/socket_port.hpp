#ifndef SOCKET_PORT_HPP
#define SOCKET_PORT_HPP
#include "sock_base.hpp"

namespace net{
    /** not support socket family return -1 */
    int get_sock_port(const sockaddr* sa);
    bool sock_cmp_port(const sockaddr *sa1, const sockaddr *sa2);

};



#endif
