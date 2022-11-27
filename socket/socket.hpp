#ifndef NET_SOCKET_HPP
#define NET_SOCKET_HPP

#define LISTENQ 16
#include "sock_base.hpp"
#include "net_address.hpp"

namespace net{
	
	::std::string sock_ntop(const sockaddr* sa, socklen_t addrlen);
	bool sock_cmp_port(const sockaddr *sa1, const sockaddr *sa2);
	bool sock_cmp_port(const sockaddr *sa1, const sockaddr *sa2);

	enum class ConnectType {
		TCP, UDP, NONE =- 1
	};

	class Socket {
		private:
			int sockFd = -1;
			using SA = sockaddr;
			using string = ::std::string;
			using Address = ::net::ip::Address;
			Address _address;
			void listen(int backlog);
			void init_socket(const ip::ProtocolInfo& proto);
			int tcp_connect(const string& host, const int port);
			int udp_connect(const string& host, const int port);
			ConnectType conn_type = ConnectType::NONE;
		public:
			Socket() = default;
			Socket(Address address);
			Socket(int sockFd);
			Socket(const Socket& s);
			//初始化一个指定的sockfd
			Socket(const ConnectType& cType, const IPType iType);
			// 针对host所支持的协议类型进行sockfd初始化
			Socket(const string host, int port, const ConnectType& cType);
			//if type value is ProtocolType::ANY,  will connect first connect success host
			void connect(const string& host, const int port, const ConnectType type = ConnectType::TCP);
			//tcp server
			void listen(const string& host, const int port);
			//udp server
			void bind(const string& host, const int port);
			Socket accept();
			~Socket();
			Address getAddress() const noexcept;
			int operator()(){return sockFd;}
	};
};

#endif
