#include "account.hpp"


using namespace std;


int sendMessage ( string sourceName, string targetName, string message ) {

    connections[targetName].call<int>( "recvMessage", sourceName, message );

    return 0;
    
}


int boardcast ( string sourceName, string targetGroupName, string message ) {

    for ( auto eachUsername : groups[targetGroupName].members ) {
        connections[eachUsername].call<int>( "recvGroupMessage", sourceName, targetGroupName,message );
    }

    return 0;

}
