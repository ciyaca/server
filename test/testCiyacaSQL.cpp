#include <iostream>
#include <mysql/mysql.h>

using namespace std;

MYSQL ciyacaSQL;

string checkPosts( int quality ){

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
            sumPostsString += row[1]+4;   // post_string
        }
        sumPostsString += "</lis>";

        mysql_free_result( result );
        return sumPostsString;
    }

}

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

    post(-1, "jaskfslakdfjkdskfdslkfd");
    cout<<checkPosts(3)<<endl;
}
