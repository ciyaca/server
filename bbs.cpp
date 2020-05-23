#include <msgpack.hpp>

#include "account.hpp"


using namespace std;


map<string, map<string, string>> postMap;


int post ( string username, string title, string body ) {

    postMap[title][username] = body;

    cout<<"new post: [ "<<title<<" : "<<body<<" ]"<<endl;
    return 0;

}


int replyPost ( string username, string title, string body ) {

    postMap[title][username] = body;

    cout<<"new replyPost: [ "<<title<<" : "<<body<<" ]"<<endl;
    return 0;

}


string checkPosts( string username, int quantity ) {

    map<string, map<string, string>> reqPostMap;
    reqPostMap.insert( postMap.begin(), postMap.end() );  // test only waiting for debug

    stringstream buffer;
    msgpack::pack( buffer, reqPostMap );

    auto conn = connections.find( username );
    conn->second.call<int>( "recvPost", buffer.str() );

    return 0;

}
