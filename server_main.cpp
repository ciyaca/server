#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "account.hpp"
#include "im.hpp"


using namespace std;


int main() {

    thread addOnlineClientThread { []() {
        FeverRPC::Factory factory;
        while (true) {
            FeverRPC::Caller newCaller = factory.accept();
            string username = newCaller.call<string>( "getUsername" );
            connections.insert( pair{username, newCaller} );
        }
    }};
    thread_guard ag( addOnlineClientThread );

    while ( true ) {
        thread serveOneClientTread { []() {
            FeverRPC::Server rpc;
            rpc.bind("login", login);
            rpc.bind("regist", regist);
            rpc.bind("sendMessage", sendMessage);
            rpc.c2s();
        }};
        thread_guard sg( serveOneClientTread );
    }

    return 0;

}
