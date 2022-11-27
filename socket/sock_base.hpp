#ifndef SOCK_BASE_HPP
#define SOCK_BASE_HPP
#include <sys/types.h> /* basic system data types */
#include <sys/socket.h>/* basic socket definitions */
#include <sys/un.h>
#include <netinet/in.h> /* sockaddr_in and other Internet definitions */
#include <arpa/inet.h>
#include <string>

namespace net{


enum class ProtocolType : int {
	ANY, TCP, UDP, SCTP
};

enum class IPType : int {
	ANY, IPv4, IPv6
};

};

#endif
