PROGRAM_NAME = interview2
CXX = g++
RM := rm -f
CXXFLAGS = -std=c++17 -g3 -pthread -gdwarf-4 -DLinux -fPIC -Wno-deprecated -pipe
STRICT_FLAGS = -Wall -Werror -Wextra -Wpedantic -Wvla -Wnull-dereference -Wswitch-enum 
#MKDIR := $(shell mkdir build 2>&1 /dev/null)

# tell me where to find boost
BOOST_INC = /usr/local/include/boost
BOOST_LIB = /usr/local/lib

# "compiler=..." will override CXX
ifeq "clang" "$(compiler)"
    CXX = /opt/clang-latest/bin/clang++
else ifeq "gcc" "$(compiler)"
    CXX = g++
else ifneq "" "$(compiler)"
    $(error unknown compiler $(compiler))
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
        question1.o \
        question2.o \
        question3.o \
        question4.o \
        question5.o \
        question6.o \
        question7.o

$(PROGRAM_NAME): $(OBJS) 
	@echo " "
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(link_parameters)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

question1.o: question1.cpp
	$(CXX) -c $(CXXFLAGS) question1.cpp

question2.o: question2.cpp
	$(CXX) -c $(CXXFLAGS) question2.cpp

question3.o: question3.cpp
	$(CXX) -c $(CXXFLAGS) question3.cpp

question4.o: question4.cpp
	$(CXX) -c $(CXXFLAGS) question4.cpp

question5.o: question5.cpp
	$(CXX) -c $(CXXFLAGS) question5.cpp

question6.o: question6.cpp
	$(CXX) -c $(CXXFLAGS) question6.cpp

question7.o: question7.cpp
	$(CXX) -c $(CXXFLAGS) question7.cpp

clean:
	@-$(RM) $(OBJS) 2>&1 >/dev/null
	@-$(RM) $(PROGRAM_NAME)
