#include "net_host.hpp"
#include "exceptions.hpp"

namespace net::host 
{
    Host::Host(string host):host(host){

    }
    Host::~Host(){
        if(res != nullptr){
            ::freeaddrinfo(res);
            res = nullptr;
        }
    }
    ::std::vector<ip::Address> Host::_getAddress(SockType type, SockFamily family, SockProtocol protocol, AddrFlags flags, const string& serv){
        addrinfo hints;
        bzero(&hints, sizeof(addrinfo));
        hints.ai_flags = static_cast<int> (flags); //返回主机的规范名字
        hints.ai_family = static_cast<int>(family); // other AF_INET AF_INET6
        hints.ai_socktype = static_cast<int>(type);          //torher SOCK_STREAM, SOCK_DGRAM
        hints.ai_protocol = static_cast<int>(protocol);
        int n;
        const char *hp = host.empty() ? NULL:host.c_str();
        const char *sp = serv.empty() ? NULL:serv.c_str();
        if( (n = getaddrinfo(hp, sp, &hints, &res)) == !0){
            throw exception::HostException(ERROR_INFO(::gai_strerror(n)));
        }
        addrinfo* rts = res;
        using vAddress = ::std::vector<ip::Address>;

        vAddress rets;
        if(res == nullptr){
            throw exception::HostException(ERROR_INFO("unknow host address: " + host));
        }

        do{
            ip::ProtocolInfo pi;
            pi.family = res->ai_family;
            pi.protocol = res->ai_protocol;
            pi.type = res->ai_socktype;
            rets.push_back(ip::Address(*res->ai_addr, pi, res->ai_addrlen));
        }while ((rts = rts->ai_next) != NULL);
        
        return rets;
    }


    ::std::vector<ip::Address> Host::getAddress(AddrFlags flags, const string& serv, const ProtocolType pt, const IPType itype){
        SockFamily family = SockFamily::UNSPEC;
        SockType type = SockType::ANY;
        SockProtocol protocol = SockProtocol::ANY;

        switch (pt)
        {
            case ProtocolType::ANY : {
                family = SockFamily::UNSPEC;
                type = SockType::ANY;
                protocol = SockProtocol::ANY;
                break;
            }
            case ProtocolType::TCP :{
                type = SockType::STREAM;
                break;
            }
            case ProtocolType :: UDP :{
                type = SockType::DGRAM;
                break;
            }
            case ProtocolType :: SCTP :{
                type = SockType::SEQPACKET;
                break;
            }
            default : throw exception::HostException(ERROR_INFO("not support protocol type"));
        }

        switch (itype)
        {
            case IPType::ANY :{
                family = SockFamily::UNSPEC;
                break;
            }
            case IPType::IPv4 :{
                family = SockFamily::INET;
                break;
            }
            case IPType::IPv6 : {
                family = SockFamily::INET6;
                break;
            }
            
            default: throw exception::HostException(ERROR_INFO("not support ip type"));
        }

        return _getAddress(type, family, protocol, flags, serv);
    }
};