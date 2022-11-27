#include "socket_port.hpp"
#include "exceptions.hpp"

namespace net{
    bool sock_cmp_port(const sockaddr* sa1, const sockaddr* sa2){
        if(sa1->sa_family != sa2->sa_family){
            return false;
        }

        switch(sa1->sa_family){
            case AF_INET : {
                return (((sockaddr_in *)sa1)->sin_port ==
                        ((sockaddr_in *)sa2)->sin_port);
            }
#ifdef IPV6
            case AF_INET6 : {
                return (((sockaddr_in6 *)sa1)->sin6_port ==
                        ((sockaddr_in6 *)sa2)->sin6_port);
            }
#endif
            default : return true;
        }

    }
    
    /***/
    int get_sock_port(const sockaddr* sa){
        auto family = sa->sa_family;
        switch(family) {
            case AF_INET : {
                const sockaddr_in *sin = (struct sockaddr_in*)sa;
                return ntohs(sin->sin_port);
             }
#ifdef IPV6
            case AF_INET6 : {
                const sockaddr_in6 *sin6 = (struct sockaddr_in6*)sa;
                return ntohs(sin6->sin6_port);
            }
#endif

            default : return -1;

        }
        return -1;
    }
};
