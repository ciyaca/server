INCLUDE=-I../feverrpc-ng/includes

bin/%.o:%.cpp
	g++ -c $< ${MSGPACK} ${INCLUDE} --std=c++17 -o $@ $(CFLAGS)

bin/%.o:../feverrpc-ng/src/%.cpp ../feverrpc-ng/includes/feverrpc/%.hpp
	g++ -c $< ${MSGPACK} ${INCLUDE} --std=c++17 -o $@ $(CFLAGS)


all: bin server

.PHONY: clean

clean:
	rm -r bin

server: bin/server_main.o bin/account.o bin/im.o bin/feverrpc.o bin/feverrpc-factory.o bin/utils.o bin/feverrpc-server.o
	g++ $^ -o bin/$@ -pthread ${INCLUDE}

bin:
	mkdir bin


