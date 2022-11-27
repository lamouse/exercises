#ifndef SOCK_IFI_HPP
#define SOCK_IFI_HPP

#include "sock_base.hpp"
#include <net/if.h>
#include <vector>

/**
 * 系统接口信息
 * 
 */

namespace net{
    class Ifi {
        private:
            using string = ::std::string;
            string  ifi_name;    // interface name
            short   ifi_index;    //interface index
            short   ifi_mtu;      //interface MTU
            string  ifi_haddr;   //hardware address
            short   ifi_flags;      //IF_xxx constants from <net/if.h>
            short   ifi_my_flags;   //our own IFI_xxx flags
            sockaddr_storage    ifi_addr;   //primary address
            sockaddr_storage    ifi_brdaddr;    //broadcast address
            sockaddr_storage    ifi_dstaddr;     //destination address
            Ifi() = default;
        public:
            Ifi(const Ifi& ifi);
            Ifi(const Ifi&& ifi);
            Ifi operator=(const Ifi& rhs);
            Ifi operator=(const Ifi&& rhs);

            string name()const noexcept;
            short index()const noexcept;
            short mtu()const noexcept;
            string haddr()const noexcept;
            short flags()const noexcept;
            short myflags()const noexcept;
            bool has_flag(short flag)const noexcept;
            bool has_myflag(short flag)const noexcept;
    };
    
};

#endif