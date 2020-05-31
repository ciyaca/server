#include <msgpack.hpp>

#include "account.hpp"


using namespace std;


int post ( string postBody ) {

    string queryStr = "INSERT INTO posts (post_string) VALUES ('" + postBody + "');";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"failed to post: [ "<<title<<" : "<<body<<" ]"<<endl;
        return -1;
    } else {
        cout<<"new post: [ "<<title<<" : "<<body<<" ]"<<endl;
        return 1;
    }

}


string checkPostFromID( int post_id ){

    string queryStr = "SELECT post_string FROM posts WHERE post_id=" + to_string( post_id ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check post failed!"<<endl;
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

    string queryStr = "SELECT * FROM posts ORDER BY post_id DESC 0," + to_string( quality ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check posts failed!"<<endl;
        return "check posts failed!";
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        string sumPostsString = "";
        
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            sumPostsString += row[0];   // post_id
            sumPostsString += row[1];   // post_string
        }

        mysql_free_result( result );
        return sumPostsString;
    }

}