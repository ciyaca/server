#include "account.hpp"


using namespace std;


vector<Account> accounts;
vector<Connection> connections;
vector<Group> groups;


Account::Account ( string _username, string _password ) : username(_username), password(_password) {}

Connection::Connection ( string _username, FeverRPC::Caller _caller ) : username(_username), caller(_caller) {}

Group::Group ( string _groupName ) : groupName(_groupName) {}


int Group::addMember ( string username ) {

    for ( auto eachConnection : connections ) {
        if ( eachConnection.username == username ) {
            this->groupMembers.push_back( eachConnection );
            break;
        }
    }

    return 0;

}


int Group::removeMember( string username ) {

    for ( auto eachConnection = this->groupMembers.begin(); eachConnection != this->groupMembers.end(); eachConnection++ ) {
        if ( (*eachConnection).username == username ) {
            this->groupMembers.erase( eachConnection );
            break;
        }
    }

    return 0;

}


int regist ( string username, string password ) {

    for ( auto eachAccount : accounts ) {
        if ( eachAccount.username == username ) {
            return -1;
        }
    }

    Account account( username, password );
    accounts.push_back( account );
    return 1;

}


int login ( string username, string password ) {

    for ( auto eachAccount : accounts ) {
        if ( eachAccount.username == username ) {
            if ( eachAccount.password == password ) {
                return 1;
            } else {
                return -1;
            }
        }
    }

    return -2;

}


int newGroup ( string username, string groupName ) {

    Group group( groupName );
    group.addMember( username );
    groups.push_back( group );

    return 0;

}


int joinGroup ( string username, string groupName ) {

    for ( auto eachGroup : groups ) {
        if ( eachGroup.groupName == groupName ) {
            eachGroup.addMember( username );
            break;
        }
    }

    return 0;

} 


int exitGroup ( string username, string groupName ) {

    for ( auto eachGroup : groups ) {
        if ( eachGroup.groupName == groupName ) {
            eachGroup.removeMember( username );
            break;
        }
    }

    return 0;

}
