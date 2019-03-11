#
# Makefile
#

# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c99 -Wall -Werror -fPIC
LDFLAGS = -shared

# space-separated list of header files
HDRS = $(realpath quick_sort.h)

# target
TARGET = quick_sort

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = $(realpath quick_sort.c)

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(TARGET): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).so $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(TARGET) *.o