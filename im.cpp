#include "sql/sql.hpp"
#include "account.hpp"


using namespace std;


int sendMessage ( string sourceName, string targetName, string message, int flag=0 ) {

    if( flag == 0 ){

        auto iter = connections.find( targetName );
        iter->second.call<int>( "recvMessage", sourceName, message );
        cout << "sendMessage single: ";
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