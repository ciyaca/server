#include "account.hpp"


using namespace std;


int sendMessage ( string sourceName, string targetName, string message ) {

    auto iter = connections.find( targetName );
    iter->second.call<int>( "recvMessage", sourceName, message );

    cout<<"from: "<<sourceName<<"; to: "<<targetName<<endl<<"[ "<<message<<" ]"<<endl;
    return 0;
    
}


int boardcast ( string sourceName, string targetGroupName, string message ) {

    string queryStr = "SELECT username FROM grp_usr WHERE groupname='" + targetGroupName + "';";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<targetGroupName<<" not exist!"<<endl;
        return -1;
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            auto iter = connections.find( row[0] );
            iter->second.call<int>( "recvMessage", sourceName, targetGroupName, message );
            cout<<"From: "<<sourceName<<" To: "<<row[0]<<endl<<"[ "<<message<<" ]"<<endl;
        }

        mysql_free_result( result );
        return 1;
    }

}
