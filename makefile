INCLUDE=-I../feverrpc-ng/includes
MYSQL=`mysql_config --cflags --libs`

bin/%.o:%.cpp 
	g++ -c $< ${MSGPACK} ${INCLUDE} --std=c++17 -o $@ $(CFLAGS)

bin/%.o:../feverrpc-ng/src/%.cpp ../feverrpc-ng/includes/feverrpc/%.hpp
	g++ -c $< ${MSGPACK} ${INCLUDE} --std=c++17 -o $@ $(CFLAGS)

bin/sql.o:sql/sql.cpp
	g++ -c $< ${MYSQL} --std=c++17 -o $@ $(CFLAGS)

all: bin server

.PHONY: clean

clean:
	rm -r bin

server: bin/server_main.o bin/account.o bin/im.o bin/bbs.o bin/sql.o bin/feverrpc.o bin/feverrpc-factory.o bin/utils.o bin/feverrpc-server.o
	g++ $^ -pthread ${INCLUDE} ${MYSQL} -o bin/$@

bin:
	mkdir bin


