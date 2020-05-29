#include <iostream>
#include <mysql/mysql.h>

using namespace std;

MYSQL ciyacaSQL;

int regist ( string username, string password ) {

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
    cout<< queryStr<<endl;

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"join "<<groupName<<" failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        cout<<username<<" is in "<<groupName<<" now!"<<endl;
        return 1;
    }

} 


int exitGroup ( string username, string groupName ) {

    string queryStr = "DELETE FROM grp_usr WHERE group='" + groupName + "' AND username='" + username + "';";
    
    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"exit "<<groupName<<" failed!"<<endl;
        return -1;
    } else {
        cout<<username<<" is not in "<<groupName<<" now!"<<endl;
        return 1;
    }

}


int boardcast ( string sourceName, string targetGroupName, string message ) {

    string queryStr = "SELECT username FROM grp_usr WHERE groupname='" + targetGroupName + "';";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<targetGroupName<<" not exist!"<<endl;
        return -1;
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        cout<<mysql_num_rows( result )<<endl;
        
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            cout<<"From: "<<sourceName<<" To: "<<row[0]<<endl<<"[ "<<message<<" ]"<<endl;
        }

        mysql_free_result( result );
        return 1;
    }

}


int ciyacaSqlInit() {

    mysql_init( &ciyacaSQL );

    if( mysql_real_connect( &ciyacaSQL, "127.0.0.1", "root", "124901", "ciyacaSQL", 3306, NULL, CLIENT_FOUND_ROWS ) ) {
        cout << "Connect to ciyaca SQL successfully!" << endl;
        return 1;
    } else {
        cout << "Failed to connect to ciyaca SQL!" << endl;
        return -1;
    }

}


int main() {

    ciyacaSqlInit();

    boardcast("sender", "grp1", "hello");


}
