#include "account.hpp"


using namespace std;


map<string, string> accounts;
map<string, FeverRPC::Caller> connections;
map<string, Group> groups;


Group::Group ( string username, FeverRPC::Caller caller ) {

    memberConnections[username] = caller;

}


int Group::addMember ( string username ) {

    this->memberConnections[username] = connections[username];

    return 0;

}


int Group::removeMember( string username ) {

    this->memberConnections.erase( this-> memberConnections.find( username ) );

    return 0;

}


int regist ( string username, string password ) {

    if ( accounts.find( username ) == accounts.end() ) {
        accounts[username] = password;
        return 1;
    } else {
        return -1;
    }

}


int login ( string username, string password ) {

    if ( accounts.find( username ) != accounts.end() ) {
        if ( accounts[username] == password ) {
            return 1;
        } else {
            return -1;
        }
    } else {
        return -2;
    }

}


int newGroup ( string username, string groupName ) {

    groups[groupName] = Group( username, connections[username] );

    return 0;

}


int joinGroup ( string username, string groupName ) {

    groups[groupName].addMember( username );

    return 0;

} 


int exitGroup ( string username, string groupName ) {

    groups[groupName].removeMember( username );

    return 0;

}
