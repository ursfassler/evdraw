
all: testapp

CPPFLAGS = -g -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror
INCLUDE_DIR = .

APP_SRC=$(wildcard core/*.cpp)
APP_OBJ=$(APP_SRC:.cpp=.o)

TEST_SRC=$(wildcard test/*.cpp test/core/*.cpp)
TEST_OBJ=$(TEST_SRC:.cpp=.o)

TEST_OBJ += $(APP_OBJ)

MAKEDEPEND = gcc -M $(CPPFLAGS) -o $*.d $<

%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) -I $(INCLUDE_DIR)

testapp: $(TEST_OBJ)
	gcc -lstdc++ -lcppunit -ldl $^ -o $@

clean:
	rm -f testapp $(APP_OBJ) $(TEST_OBJ)

