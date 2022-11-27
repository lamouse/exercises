CXX=g++
CXX_FLAGS = -std=c++20 -Wall -g -DIPV6 -lpthread
INCLUDES = ./
LFLAGS = 
LIBS = 
SRCS = socket.cc main.cc socket_utils.cc socket_port.cc socket_addr.cc net_address.cc net_host.cc ifi.cc rtt.cc
OBJS = $(SRCS:.cc = .o)
MAIN = main.out

$(MAIN) : $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $(MAIN) $(OBJS) ${LFLAGS} ${LIBS}

socket.o : socket.hpp exceptions.hpp sock_base.hpp sock_utils.hpp
main.o : socket.hpp exceptions.hpp

.c.o:
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean depend #表示clean是个伪目标
clean:
	rm -rf *.o
depend:
	makedepend $(INCLUDES) $^

