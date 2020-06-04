#include "sql/sql.hpp"
#include "account.hpp"


using namespace std;


int storeMessage( string sourceName, string targetName, string message){

    string queryStr = "INSERT INTO history_message (source_name, target_name, message) VALUES ('" + sourceName + "','" + targetName + "','" + message + "');";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"store failed! "<<mysql_error( &ciyacaSQL )<<endl;
        return -1;
    } else {
        return 1;
    }
}


int sendMessage ( string sourceName, string targetName, string message, int flag=0 ) {

    if( flag == 0 ){

        auto iter = connections.find( targetName );

        if((iter == connections.end()) == false)
            iter->second.call<int>( "recvMessage", sourceName, message );

        storeMessage( sourceName, targetName, message );

        cout<<"from: "<<sourceName<<"; to: "<<targetName<<endl<<"[ "<<message<<" ]"<<endl;
        return 0;

    } else {

        string queryStr = "SELECT username FROM grp_usr WHERE groupname='" + targetName + "';";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<targetName<<" not exist!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
            return -1;
        } else {
            MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
            
            for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
                MYSQL_ROW row = mysql_fetch_row( result );
                auto iter = connections.find( row[0] );
                cout << "sendMessage: ";
                iter->second.call<int>( "recvMessage", sourceName, targetName, message );
                cout<<"From: "<<sourceName<<" To: "<<row[0]<<endl<<"[ "<<message<<" ]"<<endl;
            }

            mysql_free_result( result );
            return 1;
        }

    }

}


int sendFile( string sourceName, string targetName, string fileName, vector<char> fileData, int flag=0 ){

    cout << "sendFile: " << sourceName << endl
        << targetName << endl
        << fileData.size() << endl
        << flag << endl;

    if( flag == 0 ){

        auto iter = connections.find( targetName );
        iter->second.call<int>( "recvFile", sourceName, targetName, fileName, fileData );

        cout<<"from: "<<sourceName<<"; to: "<<targetName<<endl<<"file :[ "<<fileName<<" ]"<<endl;
        return 0;

    } else {

        string queryStr = "SELECT username FROM grp_usr WHERE groupname='" + targetName + "';";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<targetName<<" not exist!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
            return -1;
        } else {
            MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
            
            for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
                MYSQL_ROW row = mysql_fetch_row( result );
                auto iter = connections.find( row[0] );
                iter->second.call<int>( "recvFile", sourceName, targetName, fileName, fileData );
                cout<<"From: "<<sourceName<<" To: "<<row[0]<<endl<<"file: [ "<<fileName<<" ]"<<endl;
            }

            mysql_free_result( result );
            return 1;
        }

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
            auto iter = connections.find( username );
            iter->second.call<int>( "recvMessage", row[0], row[1] );
            cout<<"From: "<<row[0]<<" To: "<<username<<endl<<"[ "<<row[1]<<" ]"<<endl;
        }

        mysql_free_result( result );
        return 1;
    }

}
