#include "socket_utils.hpp"

namespace net{
    int sockfd_to_family(int sockfd){
        sockaddr_storage ss;
        socklen_t len;
        len = sizeof(ss);
        if(::getsockname(sockfd, (sockaddr*)&ss, &len) < 0){
            return -1;
        }
        return ss.ss_family;
    }

};