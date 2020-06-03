#include <iostream>
#include <mysql/mysql.h>

using namespace std;

MYSQL ciyacaSQL;

int storeMessage( string sourceName, string targetName, string message){

    string queryStr = "INSERT INTO history_message (source_name, target_name, message) VALUES ('" + sourceName + "','" + targetName + "','" + message + "');";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"store failed! "<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        return 1;
    }
}

int checkHistoryMessage( string username ){

    string queryStr = "SELECT source_name,message FROM history_message WHERE target_name='" + username + "';";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<username<<" not exist!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            // auto iter = connections.find( username );
            // iter->second.call<int>( "recvMessage", row[0], row[1] );
            cout<<"From: "<<row[0]<<" To: "<<username<<endl<<"[ "<<row[1]<<" ]"<<endl;
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

    checkHistoryMessage( "TO");
}
