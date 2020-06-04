#include "account.hpp"
#include "sql/sql.hpp"

using namespace std;


map<string, FeverRPC::Caller> connections;


int regist ( string username, string password ) {
    cout << "regist:\n" << endl;

    string queryStr = "INSERT INTO usr_pwd (username, password) VALUES ('" + username + "','" + password + "');";

    if ( mysql_query( &ciyacaSQL, queryStr.c_str() ) ) {
        cout<<username<<" regist failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
	    cout<<username<<" regist success!"<<endl;
        return 1;
    }

}


int login ( string username, string password ) {

    string queryStr = "SELECT password FROM usr_pwd WHERE username = '" + username + "';";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<username<<" not exist!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -2;
    } else {
        MYSQL_RES* result = mysql_use_result( &ciyacaSQL );
        MYSQL_ROW row = mysql_fetch_row( result );
        string realPassword( row[0] );
        mysql_free_result( result );
        if( password == realPassword ){
            cout<<username<<" login success!"<<endl;
            return 1;
        } else {
            cout<<username<<" wrong password!"<<endl;
            return -1;
        }
    }
}


int joinGroup ( string username, string groupName ) {

    string queryStr = "INSERT INTO grp_usr (groupname, username) VALUES ('" + groupName + "','" + username + "');";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"join "<<groupName<<" failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        cout<<username<<" is in "<<groupName<<" now!"<<endl;
        return 1;
    }

} 


int exitGroup ( string username, string groupName ) {

    string queryStr = "DELETE FROM grp_usr WHERE groupname='" + groupName + "' AND username='" + username + "';";
    
    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"exit "<<groupName<<" failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        cout<<username<<" is not in "<<groupName<<" now!"<<endl;
        return 1;
    }

}
