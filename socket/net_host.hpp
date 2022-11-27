#ifndef NET_HOST_HPP
#define NET_HOST_HPP

#include "sock_base.hpp"
#include "net_address.hpp"
#include <netdb.h>
#include <vector>

namespace net{
    enum class SockFamily : int {
	INET = AF_INET,
	INET6 = AF_INET6,
	LOCAL = AF_LOCAL,
	ROUTE = AF_ROUTE,
	UNSPEC = AF_UNSPEC
};

enum class SockType : int {
	ANY = 0,
	STREAM = SOCK_STREAM,
	DGRAM = SOCK_DGRAM,
	SEQPACKET = SOCK_SEQPACKET,
	RAW = SOCK_RAW,
};

enum class SockProtocol : int {
	ANY = 0,
	TCP = IPPROTO_TCP,
	UDP = IPPROTO_UDP,
	SCTP = IPPROTO_SCTP
};
}

namespace net :: host {

    enum class AddrFlags{
        UNSET = 0,              //默认0         
        PASSIVE = AI_PASSIVE, //将套接字用于被动打开
        CANONNAME = AI_CANONNAME, //getaddrinfo返回主机的规范名字
        NUMERICHOST = AI_NUMERICHOST, // 防止任何类型的名字到地址映射, hostname参数必须是一个地址串
        NUMERICSERV = AI_NUMERICSERV, // 防止任何类型的名字到地址映射, service参数必须是一个十进制的端口号
        V4MAPPED = AI_V4MAPPED,         // 如果同时制定ai_family的值为AF_NET6， 没有可用的AAAA地址时返回对应的IPV4映射的IPV6地址
        ALL = AI_ALL,                   //如果同时指定AI_V4MAPPED，除了返回AAAA的IPV6地址，同时返回A记录对应IPV4映射的IPV6地址
        ADDRCONFIG = AI_ADDRCONFIG      //只查找与所在主机回馈接口以外的的网络接口配置的IP地址版本一致的地址
    };

    class Host{
        private:
            using string = ::std::string;
            using Address = ::net::ip::Address;
            addrinfo *res = nullptr;
            string host;
            ::std::vector<Address> _getAddress(SockType type, SockFamily family, SockProtocol protocol, AddrFlags flags, const string& serv);
        public:
            Host(string host);
            /* default return all address*/
            ::std::vector<Address> getAddress(AddrFlags flags, const string& serv, const ProtocolType pt = ProtocolType::ANY, const IPType itype = IPType::ANY);

            ~Host();
            
    };
};

#endif