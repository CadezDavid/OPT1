CPPFLAGS=-Wall
TARGETS=dn2
CPP=g++
RM=rm -f

SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS=$(subst .cc,.o,$(SRCS))


dn2: $(SRCS)
	$(CPP) $(CPPFLAGS) -o dn2 $(OBJS)

all:
	dn2;

clean:
	$(RM) $(TARGETS)
