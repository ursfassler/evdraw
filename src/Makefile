
all: testapp

CPPFLAGS = -g -std=c++11 -Wall -Wextra -pedantic -Weffc++
INCLUDE_DIR = .
APP_OBJ = core/Endpoint.o core/Segment.o core/InstancePort.o core/Connection.o core/ConnectionFactory.o
TEST_OBJ = $(APP_OBJ) test/main.o test/core/EndpointTest.o test/core/SegmentTest.o test/core/InstancePortTest.o test/core/ConnectionTest.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) -I $(INCLUDE_DIR)

testapp: $(TEST_OBJ)
	gcc -lstdc++ -lcppunit -ldl $^ -o $@

clean:
	rm -f testapp $(APP_OBJ) $(TEST_OBJ)

