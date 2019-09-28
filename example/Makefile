# SOURCE = $(wildcard *.cpp)
# SOURCE_NAMES = $(notdir $(SOURCE))
# TARGET = $(patsubst %.cpp, %, $(SOURCE_NAMES))
# TARGET_DIR = ./bin/
# TARGET_NAMES := $(addprefix $(TARGET_DIR), $(TARGET))
# # TARGETS := $(subst "./", "./bin/", $(TARGETS_A))

# INCLUDE_PATH = ../include/
 
# CC = g++
# CFLAGS = -Wall -g

# all:
	# $(TARGET_NAMES)
 
# $(TARGET_NAMES):%:%.cpp
	# $(CC) $(CFLAGS) $< -o $@ -I $(INCLUDE_PATH)

# recompile:clean all

# clean:
	# rm -f $(TARGETS)
	
# .PHONY:clean all recompile


SOURCE = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp, %, $(SOURCE))

CC = g++
CFLAGS = -Wall -g

all:$(TARGETS)

$(TARGETS):%:%.cpp
		$(CC) $< $(CFLAGS) -o $@ -I ../include/

.PHONY:clean all
clean:
	-rm -rf $(TARGETS)