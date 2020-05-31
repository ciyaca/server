#include "account.hpp"


int post( int post_id, string postBody );
string checkPostFromID( int post_id );
string checkPosts( int quality );
int uploadFile( string fileName, vector<char> fileData );
vector<char> downloadFile( string fileName );