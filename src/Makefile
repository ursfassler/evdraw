
CC=clang

all: testapp

CPPFLAGS = -g -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror
LINKFLAGS = -ltinyxml
INCLUDE_DIR = .

SRC=$(wildcard core/*/*.cpp core/*.cpp file/*.cpp file/*/*.cpp unittest/*.cpp unittest/*/*.cpp unittest/*/*/*.cpp)
OBJ=$(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) -I $(INCLUDE_DIR)

testapp: unittest/main.o $(OBJ)
	$(CC) -lstdc++ -lcppunit -ldl $(LINKFLAGS) $^ -o $@

clean:
	rm -f testapp test/main.o $(OBJ)

