TARGET = junk
CXX=clang++
RM=rm -f
CPPFLAGS = --std=c++11 -fsanitize=undefined -Wall -pedantic -Wconversion

SRCS=datetime.cpp main.cpp

all: main clean run

main:
	    $(CXX) $(SRCS) $(CPPFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	    $(RM) $(OBJS)
