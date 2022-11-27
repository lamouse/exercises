#ifndef NET_EXCEPTIONS
#define NET_EXCEPTIONS
#include <system_error>
#include <stdexcept>
#include <string>

#define ERROR_INFO(msg) ::std::string("file: ") + __FILE__ +	\
							::std::string(" func: ") + __PRETTY_FUNCTION__  +	\
							::std::string(" line: ") + ::std::to_string( __LINE__ ) +	\
							::std::string(":\n\t") + msg + ::std::string("\n")
namespace net::exception{
	class BindException : public ::std::runtime_error{
		public:
			BindException(const ::std::string& msg) :
				::std::runtime_error(::std::string("BindException: ") + msg){};
	};

	
	class SocketException : public ::std::runtime_error{
		public:
			SocketException(const ::std::string& msg) : 
				::std::runtime_error(::std::string("SocketException: ") + msg){};
	};


	class ListenException : public ::std::runtime_error{
		public:
			ListenException(const ::std::string& msg) : 
				::std::runtime_error(::std::string("ListenException: ") + msg){};
	};


	class AcceptException : public ::std::runtime_error{
		public:
			AcceptException(const ::std::string& msg) : 
				::std::runtime_error(::std::string("AcceptException: ") + msg){};
	};


	class ConnectionException : public ::std::runtime_error{
		public:
			ConnectionException(const ::std::string& msg) : 
				::std::runtime_error(::std::string("ConnectionException: ") + msg){};
	};

	class HostException : public ::std::runtime_error{
		public:
			HostException(const ::std::string& msg) : 
				::std::runtime_error(::std::string("HostException: ") + msg){};
	};
};

#endif
