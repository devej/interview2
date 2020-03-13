PROGRAM_NAME = interview2
CXX = g++
#CXX = clang++
RM := rm -f
CXXFLAGS = -std=c++17 -g3 -pthread -gdwarf-4 -DLinux -fPIC -Wno-deprecated -pipe
STRICT_FLAGS = -Wall -Werror -Wextra -Wpedantic -Wvla -Wnull-dereference -Wswitch-enum
CLANG_FLAGS = -stdlib=libc++
#MKDIR := $(shell mkdir build 2>&1 /dev/null)

# tell me where to find boost
BOOST_INC = /usr/local/include/boost
BOOST_LIB = /usr/local/lib

# "compiler=..." will override CXX
ifeq "clang" "$(compiler)"
    CXX = clang++
else ifeq "gcc" "$(compiler)"
    CXX = g++
else ifneq "" "$(compiler)"
    $(error unknown compiler $(compiler))
endif

ifeq "clang++" "$(CXX)"
    CXXFLAGS += $(CLANG_FLAGS)
endif

# default to debug
# can override with config=(anything).  e.g. make -j2 config=release -f Makefile
config := debug

ifeq "debug" "$(config)"
    CXXFLAGS += -O0
else
    CXXFLAGS += -DNDEBUG -O3
endif

CXXFLAGS += -I $(BOOST_INC) $(STRICT_FLAGS)

LIBRARY_DIRECTORIES = -L$(BOOST_LIB)
LIBRARY_COMMON = -ldl -lrt

link_parameters = \
    $(LIBRARY_DIRECTORIES) \
    $(LIBRARY_COMMON)

OBJS =  main.o \
        fizbuz.o \
        operator_plus.o \
        signatures.o \
        assignment_operator.o \
        singleton.o \
        queue.o \
        vector_upper_bound.o \
        job_chain.o \
        airport.o \
        robo_trader.o

$(PROGRAM_NAME): $(OBJS) 
	@echo " "
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(link_parameters)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

fizbuz.o: fizbuz.cpp
	$(CXX) -c $(CXXFLAGS) fizbuz.cpp

operator_plus.o: operator_plus.cpp
	$(CXX) -c $(CXXFLAGS) operator_plus.cpp

signatures.o: signatures.cpp
	$(CXX) -c $(CXXFLAGS) signatures.cpp

assignment_operator.o: assignment_operator.cpp
	$(CXX) -c $(CXXFLAGS) assignment_operator.cpp

singleton.o: singleton.cpp
	$(CXX) -c $(CXXFLAGS) singleton.cpp

queue.o: queue.cpp
	$(CXX) -c $(CXXFLAGS) queue.cpp

vector_upper_bound.o: vector_upper_bound.cpp
	$(CXX) -c $(CXXFLAGS) vector_upper_bound.cpp

job_chain.o: job_chain.cpp
	$(CXX) -c $(CXXFLAGS) job_chain.cpp

airport.o: airport.cpp
	$(CXX) -c $(CXXFLAGS) airport.cpp

robo_trader.o: robo_trader.cpp
	$(CXX) -c $(CXXFLAGS) robo_trader.cpp


clean:
	@-$(RM) $(OBJS) 2>&1 >/dev/null
	@-$(RM) $(PROGRAM_NAME)
