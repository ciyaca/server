#include <msgpack.hpp>

#include "account.hpp"


using namespace std;


map<string, map<string, string>> postMap;


int post ( string username, string title, string body ) {

    postMap[title][username] = body;

    return 0;

}


int reply( string username, string title, string body ) {

    postMap[title][username] = body;

    return 0;

}


string checkPosts( string username, int quantity ) {

    map<string, map<string, string>> reqPostMap;
    reqPostMap.insert( postMap.end()-quantity, postMap.end() );

    stringstream buffer;
    msgpack::pack( buffer, reqPostMap );

    auto conn = connections.find( username );
    conn->second.call<int>( "recvPost", buffer.str() );

    return 0;

}