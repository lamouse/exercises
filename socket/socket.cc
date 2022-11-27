#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "socket.hpp"
#include "socket_utils.hpp"
#include "exceptions.hpp"
#include "net_host.hpp"

#ifdef HAVE_SOCKADDR_DL_STRUCT
#include<net/if_dl.h>
#endif


namespace net{

	Socket::Socket(Address address):_address(address){
		init_socket(_address.protocol());
	}

	Socket::Socket(int sockFd):sockFd(sockFd){

	}

	Socket::Socket(const ConnectType& cType, const IPType iType){
		using namespace ::net::host;
		int family = -1;
		int type = -1;
		switch (cType)
		{
		case ConnectType::UDP:{
			type = static_cast<int>(SockType::DGRAM);
			break;
		}
		case ConnectType::TCP:{
			type = static_cast<int>(SockType::STREAM);
			break;
		}
		default:
			return;
		}
		
		switch (iType)
		{
		case IPType::IPv4:{
			type = static_cast<int>(SockFamily::INET);
			break;
		}
		case IPType::IPv6:{
			type = static_cast<int>(SockFamily::INET6);
			break;
		}
		default:
			return;
		}	
		init_socket({family, type, 0});

	}

	Socket::Socket(const string host, int port, const ConnectType& cType){
		using namespace ::net::host;
		Host h(host);
		::std::vector<ip::Address> vAddrs;
		switch (cType)
		{
		case ConnectType::UDP:{
			vAddrs = h.getAddress(AddrFlags::UNSET, ::std::to_string(port), ProtocolType::UDP);
			break;
		}
		case ConnectType::TCP:{
			vAddrs = h.getAddress(AddrFlags::UNSET, ::std::to_string(port), ProtocolType::TCP);
	
			break;
		}
		default:
			return;
		}
		
		if(!vAddrs.empty()){
			init_socket(vAddrs.begin()->protocol());
		}else{
			throw exception::SocketException(ERROR_INFO("unknow socket protocol"));
		}
	}

	Socket::Socket(const Socket& s){
		sockFd = s.sockFd;
		_address = s._address;
		conn_type = s.conn_type;
	}

	void Socket::init_socket(const ip::ProtocolInfo& proto){
		sockFd = ::socket(proto.family, proto.type, proto.protocol);
		if( sockFd < 0 ){
			throw exception::SocketException(ERROR_INFO(::strerror(errno)));
		}
	}

	int Socket::tcp_connect(const string& host, const int port){
		using namespace ::net::host;
		Host h(host);
		auto addrs = h.getAddress(AddrFlags::UNSET, ::std::to_string(port), ProtocolType::TCP);
		for(auto & addr : addrs){
			init_socket(addr.protocol());
			if(::connect(sockFd, addr.address(), addr.sock_len()) == 0){
				_address = addr;
				return 0;
			}
			close(sockFd);
		}
		return -1;
	}

	int Socket::udp_connect(const string& host, const int port){
		using namespace ::net::host;
		Host h(host);
		auto addrs = h.getAddress(AddrFlags::UNSET, ::std::to_string(port), ProtocolType::UDP);
		for(auto & addr : addrs){
			init_socket(addr.protocol());
			if(::connect(sockFd, addr.address(), addr.sock_len()) == 0){
				_address = addr;
				return 0;
			}
			close(sockFd);
		}
		return -1;
	}

	void Socket::connect(const string& host, const int port, const ConnectType type){
		int cr = -1;
		conn_type = type;
		switch (type)
		{
			case ConnectType::TCP:{
				cr = tcp_connect(host, port);
				break;
			}
			case ConnectType::UDP: {
				cr = udp_connect(host, port);
				break;
			}
			default: break;
		}

		if(cr < 0){
			throw exception::ConnectionException(ERROR_INFO(::strerror(errno)));
		}
		
	}

	void Socket::listen(int backlog){
		char* ptr;
		if((ptr = getenv("LISTENQ")) != NULL){
			backlog = atoi(ptr);
		}
		if(::listen(sockFd, backlog) < 0 ){
			throw exception::ListenException(ERROR_INFO(::strerror(errno)));
		}
	}

	void Socket::listen(const string& host, const int port){
		conn_type = ConnectType::TCP;
		using namespace ::net::host;
		Host h(host);
		const int on = 1;
		auto addrs = h.getAddress(AddrFlags::PASSIVE, ::std::to_string(port), ProtocolType::TCP);
		for(auto & addr : addrs){
			init_socket(addr.protocol());
			if(setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
				throw exception::ListenException(ERROR_INFO(::strerror(errno)));
			}

			if(::bind(sockFd, addr.address(), addr.sock_len()) == 0){
				listen(LISTENQ);
				_address = addr;
				return;
			}
			close(sockFd);
		}
		throw exception::ListenException(ERROR_INFO(::strerror(errno)));
	}

	void Socket::bind(const string& host, const int port){
			using namespace ::net::host;
		Host h(host);
		auto addrs = h.getAddress(AddrFlags::PASSIVE, ::std::to_string(port), ProtocolType::UDP);
		for(auto & addr : addrs){
			init_socket(addr.protocol());

			if(::bind(sockFd, addr.address(), addr.sock_len()) == 0){
				_address = addr;
				return;
			}
			close(sockFd);
		}
		throw exception::BindException(ERROR_INFO(::strerror(errno)));
	}

	Socket Socket::accept(){
		SA cliaddr;
		socklen_t len = sizeof(cliaddr);
		int connectFd(-1);
		while (true){
			connectFd = ::accept(sockFd, &cliaddr, &len);
			if(connectFd < 0){
				// 发送系统中断继续执行
				if(errno == EINTR){
					continue;
				}else{
					throw exception::AcceptException(ERROR_INFO(strerror(errno)));
				}
			}else{
				break;
			}
		}
		
		Socket cli(connectFd);

        cli._address = Address(cliaddr, _address.protocol(), len);
		cli.conn_type = conn_type;
		return cli;
	}

	Socket::~Socket(){
		::close(sockFd);
	}


	ip::Address Socket::getAddress()const noexcept{
		return _address;
	}

};
