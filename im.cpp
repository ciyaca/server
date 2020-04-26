#include "account.hpp"


using namespace std;


int sendMessage ( string sourceName, string targetName, string message ) {

    for( auto eachConnection : connections ) {
        if ( eachConnection.username == targetName ) {
            eachConnection.caller.call<int>( "recvMessage", sourceName, message );
            break;
        }
    }

    return 0;
    
}


int boardcast ( string sourceName, string targetGroupName, string message ) {
    
    for ( auto eachGroup : groups ) {
        if ( eachGroup.groupName == targetGroupName ) {
            for( auto eachConnection : eachGroup.groupMembers ) {
                eachConnection.caller.call<int>( "recvMessage", sourceName, message );
            }
            break;
        }
    }

    return 0;

}
