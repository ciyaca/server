#include "account.hpp"


using namespace std;


map<string, vector<pair<string, string>> postMap;


int post ( string username, string title, string body ) {

    postMap[title].push_back( pair<string, string>( username, body ) );

    return 0;

}


int reply ( string username, string title, string body ) {

    postMap[title].push_back( pair<string, string>( username, body ) );

    return 0;

}


string checkPosts ( string username, int quantity ) {

    for( eachPost = postMap.end(); eachPost != postMap.begin(); eachPost-- ) {

        

    }

}