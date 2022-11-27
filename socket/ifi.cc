#include <sstream>
#include "ifi.hpp"

namespace net{

    Ifi::Ifi(const Ifi& ifi){
        ifi_name =  ifi.ifi_name;
        ifi_index =  ifi.ifi_index;
        ifi_mtu = ifi.ifi_mtu;
        ifi_haddr = ifi.ifi_haddr;
        ifi_flags = ifi.ifi_flags;
        ifi_my_flags = ifi.ifi_my_flags;
        ifi_addr = ifi.ifi_addr;
        ifi_brdaddr = ifi.ifi_brdaddr;
        ifi_dstaddr = ifi.ifi_dstaddr;
    }
    Ifi::Ifi(const Ifi&& ifi){
        ifi_name = ::std::move(ifi.ifi_name);
        ifi_index = ::std::move(ifi.ifi_index);
        ifi_mtu = ::std::move(ifi.ifi_mtu);
        ifi_haddr = ::std::move(ifi.ifi_haddr);
        ifi_flags = ::std::move(ifi.ifi_flags);
        ifi_my_flags = ::std::move(ifi.ifi_my_flags);
        ifi_addr = ::std::move(ifi.ifi_addr);
        ifi_brdaddr = ::std::move(ifi.ifi_brdaddr);
        ifi_dstaddr = ::std::move(ifi.ifi_dstaddr);
    }
    Ifi Ifi::operator=(const Ifi& rhs){
        ifi_name = rhs.ifi_name;
        ifi_index =  rhs.ifi_index;
        ifi_mtu = rhs.ifi_mtu;
        ifi_haddr = rhs.ifi_haddr;
        ifi_flags = rhs.ifi_flags;
        ifi_my_flags = rhs.ifi_my_flags;
        ifi_addr = rhs.ifi_addr;
        ifi_brdaddr = rhs.ifi_brdaddr;
        ifi_dstaddr = rhs.ifi_dstaddr;
        return *this;
    }
    Ifi Ifi::operator=(const Ifi&& rhs){
        ifi_name = ::std::move(rhs.ifi_name);
        ifi_index = ::std::move(rhs.ifi_index);
        ifi_mtu = ::std::move(rhs.ifi_mtu);
        ifi_haddr = ::std::move(rhs.ifi_haddr);
        ifi_flags = ::std::move(rhs.ifi_flags);
        ifi_my_flags = ::std::move(rhs.ifi_my_flags);
        ifi_addr = ::std::move(rhs.ifi_addr);
        ifi_brdaddr = ::std::move(rhs.ifi_brdaddr);
        ifi_dstaddr = ::std::move(rhs.ifi_dstaddr);
        return *this;
    }

        ::std::string Ifi::name()const noexcept{
            return ifi_name;
        }
        short Ifi::index()const noexcept{
            return ifi_index;
        }
        short Ifi::mtu()const noexcept{
            return ifi_mtu;
        }
        ::std::string Ifi::haddr()const noexcept{
            return ifi_haddr;
        }
        short Ifi::flags()const noexcept{
            return ifi_flags;
        }
        short Ifi::myflags()const noexcept{
            return ifi_my_flags;
        }

        bool Ifi:: has_flag(short flag)const noexcept{
            return ifi_flags & flag;
        }

        bool Ifi:: has_myflag(short flag)const noexcept{
            return ifi_my_flags & flag;
        }
};
