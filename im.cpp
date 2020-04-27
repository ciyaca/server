#include "account.hpp"


using namespace std;


int sendMessage ( string sourceName, string targetName, string message ) {

    auto iter = connections.find( targetName );
    iter->second.call<int>( "recvMessage", sourceName, message );

    return 0;
    
}


int boardcast ( string sourceName, string targetGroupName, string message ) {

    for ( auto eachUsername : groups[targetGroupName].members ) {
        auto iter = connections.find( eachUsername );
        iter->second.call<int>( "recvGroupMessage", sourceName, targetGroupName,message );
    }

    return 0;

}
