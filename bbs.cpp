#include <fstream>

#include "account.hpp"
#include "sql/sql.hpp"


using namespace std;


int post( int post_id, string postBody ) {

    if( post_id == -1 ){
        string queryStr = "INSERT INTO posts (post_string) VALUES ('" + postBody + "');";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<"failed to post: [ "<<postBody<<" ]"<<endl<<mysql_error( &ciyacaSQL )<<endl;
            return -1;
        } else {
            cout<<"new post: [ "<<postBody<<" ]"<<endl;
            return 1;
        }
    } else {
        string queryStr = "UPDATE posts SET post_string='" + postBody + "' WHERE post_id=" + to_string( post_id ) + ";";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<"failed to reply: [ "<<postBody<<" ]"<<endl<<mysql_error( &ciyacaSQL )<<endl;
            return -1;
        } else {
            cout<<"new post: [ "<<postBody<<" ]"<<endl;
            return 1;
        }
    }

}


string checkPostFromID( int post_id ){

    string queryStr = "SELECT post_string FROM posts WHERE post_id=" + to_string( post_id ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check post failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return "chekc post failed!";
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        MYSQL_ROW row = mysql_fetch_row( result );
        string post_string = row[0];
        mysql_free_result( result );
        cout<<"check post : "<<post_string<<endl;
        return post_string;
    }

}


string checkPosts( int quality ){

    cout << "checkPosts:\n";
    string queryStr = "SELECT * FROM posts ORDER BY post_id DESC LIMIT 0," + to_string( quality ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check posts failed!"<<endl<<mysql_error( &ciyacaSQL )<<endl;
        return "check posts failed!";
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );

        string sumPostsString = "<lis>";
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            sumPostsString += "<li>\n<div>";
            sumPostsString += row[0];   // post_id
            sumPostsString += "</div>\n";
            sumPostsString += row[1] + 4;   // post_string
        }
        sumPostsString += "</lis>";

        mysql_free_result( result );
        cout << sumPostsString << endl;
        return sumPostsString;
    }

}


int uploadFile( string fileName, vector<char> fileData ){

    string path = "./net_disk/" + fileName;
    ofstream outputFile( path, ios::binary );
    outputFile.write( &fileData[0], fileData.size() );
    outputFile.close();
    cout << "uploadFile: file saved in " << path << " size = " << fileData.size() << endl;
    return 0;

}



vector<char> downloadFile( string fileName ){

    vector<char> fileData;
    string path = "./net_disk/" + fileName;
    ifstream inputFile( path, ios::binary );
    char byte_data;

    while( !inputFile.eof() ){
        inputFile.read( &byte_data, 1 );
        fileData.push_back( byte_data );
    }
    fileData.pop_back();
    inputFile.close();

    cout << "downloadFile: " << path << " size = " << fileData.size() << endl;
    return fileData;

}