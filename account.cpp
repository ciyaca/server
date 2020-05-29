#include "account.hpp"
#include "sql/sql.hpp"
#include<cstdlib>

using namespace std;


map<string, string> accounts;
map<string, FeverRPC::Caller> connections;
map<string, Group> groups;


Group::Group () {

}


Group::Group ( string username ) {

    this->members.push_back( username );

}


int Group::addMember ( string username ) {

    this->members.push_back( username );

    return 0;

}


int Group::removeMember ( string username ) {

    for ( auto eachUsername = this->members.begin(); eachUsername != this->members.end(); eachUsername++ ) {
        if ( *eachUsername == username ) {
            this->members.erase( eachUsername );
            break;
        }
    }

    return 0;

}


int regist ( string username, string password ) {

    string queryStr = "INSERT INTO user (user_name, password, nickname, signature, head_portrait_id, password_protect_id, answer) VALUES (" + username + ",md5(" + password + "),'no_nickname','no_signature',0,0,'no_answer');";

    if ( mysql_query( &ciyacaSQL, queryStr.c_str() ) ) {
        cout<<username<<" regist failed!"<<endl;
        return -1;
    } else {
	    cout<<username<<" regist success!"<<endl;
        return 1;
    }

}


int login ( string username, string password ) {

    string queryStr = "SELECT " + password + " FROM user WHERE user_name = " + username + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<username<<" not exist!"<<endl;
        return -2;
    } else {
        MYSQL_RES* result = mysql_use_result( &ciyacaSQL );
        MYSQL_ROW row = mysql_fetch_row( result );
        string realPassword( row[0] );
        if( password == realPassword ){
            cout<<username<<" login success!"<<endl;
            return 1;
        } else {
            cout<<username<<" wrong password!"<<endl;
            return -1;
        }
    }
}


int newGroup ( string username, string groupName ) {

    groups[groupName] = Group( username );

    cout<<"group "<<groupName<<" created!"<<endl;
    return 0;

}


int joinGroup ( string username, string groupName ) {

    groups[groupName].addMember( username );

    cout<<username<<" is in "<<groupName<<" now!"<<endl;
    return 0;

} 


int exitGroup ( string username, string groupName ) {

    groups[groupName].removeMember( username );

    cout<<username<<" is not in "<<groupName<<" now!"<<endl;
    return 0;

}
