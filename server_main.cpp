#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "account.hpp"
#include "im.hpp"
#include "bbs.hpp"
#include "sql/sql.hpp"


using namespace std;


int main() {

    ciyacaSqlInit();

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
            rpc.bind("joinGroup", joinGroup);
            rpc.bind("exitGroup", exitGroup);
            rpc.bind("sendMessage", sendMessage);
            rpc.bind("sendFile", sendFile);
            rpc.bind("post", post);
            rpc.bind("checkPostFromID", checkPostFromID);
            rpc.bind("checkPosts", checkPosts);
            rpc.bind("uploadFile", uploadFile);
            rpc.bind("downloadFile", downloadFile);
            rpc.bind("checkHistoryMessage", checkHistoryMessage);
            rpc.c2s();
        }};
        thread_guard sg( serveOneClientTread );
    }

    return 0;

}
