#include "socket_utils.hpp"
#include "exceptions.hpp"
#include <string.h>
namespace net{

	::std::string sock_ntop(const sockaddr* sa, socklen_t addrlen){
		char tmp[128] = {0};
		auto family = sa->sa_family;
		switch(family) {
			case AF_INET : {
				const sockaddr_in *sin = (struct sockaddr_in*)sa;
				if(::inet_ntop(family, &sin->sin_addr, tmp, sizeof(tmp)) == NULL){
					throw exception::SocketException(ERROR_INFO(::strerror(errno)));
				}
				return ::std::string(tmp);
			 }
#ifdef IPV6
			case AF_INET6 : {
				const sockaddr_in6 *sin6 = (struct sockaddr_in6*)sa;
				if(::inet_ntop(family, &sin6->sin6_addr, tmp, sizeof(tmp)) == NULL){
					throw exception::SocketException(ERROR_INFO(::strerror(errno)));
				}
				return ::std::string(tmp);
			}
#endif

#ifdef AF_UNIX
			case AF_UNIX : {
				sockaddr_un *unp = (struct sockaddr_un*)sa;
				if(unp->sun_path[0] == 0){
					::strcpy(tmp, "no path name bound");
				}else{
					snprintf(tmp, sizeof(tmp), "%s" ,unp->sun_path);
				}
				return ::std::string(tmp);
			}
#endif

#ifdef HAVE_SOCKADDR_DL_STRUCT
			case AF_LINK : {
				struct sockaddr_dl *sdl = (struct sockaddr_dl*)sa;
				if(sdl-<sdl_nlen < 0){
					snprintf(tmp, sizeof(tmp), "%*s", sdl->sdl_len,
							&sdl->sdl_data[0]);
				}else{
					snprintf(tmp, sizeof(tmp), "AF_LINK, index=%d",
							sdl->sdl_index);
				}
				return ::std::string(tmp);
			}
#endif
			default : throw exception::SocketException(ERROR_INFO("unknow protocal AF_XXXX " +
								  ::std::to_string(family)));

		}
		return ::std::string();
	}

	
	
	bool sock_cmp_addr(const sockaddr *sa1, const sockaddr *sa2){
		if(sa1->sa_family != sa2->sa_family){
			return false;
		}

		switch(sa1->sa_family){
			case AF_INET : {
				return(memcmp(&((sockaddr_in*)sa1)->sin_addr,
							  &((sockaddr_in*)sa2)->sin_addr,
							  sizeof(in_addr)));
			}
#ifdef IPV6
			case AF_INET6 : {
					return(memcmp(&((sockaddr_in6 *) sa1)->sin6_addr,
					   			  &((sockaddr_in6 *) sa2)->sin6_addr,
					   			  sizeof(in6_addr)) == 0);				
				}
#endif

#ifdef	AF_UNIX
			case AF_UNIX: {
					return(strcmp( ((sockaddr_un *) sa1)->sun_path,
					   ((sockaddr_un *) sa2)->sun_path) == 0);
			}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
			case AF_LINK: {
				return(false);		/* no idea what to compare here ? */
			}
#endif
		}

		throw exception::SocketException(ERROR_INFO(::std::string("cmp addr unknow AF_XXX") + 
						::std::to_string(sa1->sa_family)));
	}
    
};
