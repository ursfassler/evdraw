
CC=clang

all: testapp

CPPFLAGS = -g -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror
INCLUDE_DIR = .

SRC=$(wildcard core/*.cpp core/util/*.cpp core/component/*.cpp core/instance/*.cpp core/connection/*.cpp)
OBJ=$(SRC:.cpp=.o)

MAKEDEPEND = gcc -M $(CPPFLAGS) -o $*.d $<

%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) -I $(INCLUDE_DIR)

testapp: test/main.o $(OBJ)
	$(CC) -lstdc++ -lcppunit -ldl $^ -o $@

clean:
	rm -f testapp test/main.o $(OBJ)

