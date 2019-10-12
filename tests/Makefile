SOURCE = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp, %, $(SOURCE))

INCLUDE_PATH = ../include/

CC = g++
CFLAGS = -Wall -g

all:$(TARGETS)

$(TARGETS):%:%.cpp
		$(CC) $(CFLAGS) $< -o $@ -I $(INCLUDE_PATH)

recompile: clean all

clean:
	-rm -rf $(TARGETS)
	
.PHONY:clean all recompile