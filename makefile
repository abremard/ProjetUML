CPP=g++
CPPFLAGS= -DMAP -Wall -ansi -pedantic -std=c++11 -ggdb3 #Ajouter ou retirer le flag -DMAP pour tracer les contructeurs/destructeurs

MAIN=exec
SRCS=$(wildcard */*.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.h)

$(MAIN): $(OBJS) 
	$(CPP) -o $(MAIN) $(OBJS)
%.o: %.cpp $(DEPS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o $(MAIN)
