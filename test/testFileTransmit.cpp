#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int uploadFile( string fileName, vector<char> fileData ){

    string path = "../net_disk/" + fileName;
    ofstream outputFile( path, ios::binary );

    outputFile.write( &fileData[0], fileData.size() );
    outputFile.close();
    cout << "uploadFile: file saved in " << path << endl;
    return 0;
}


vector<char> downloadFile( string fileName ){

    vector<char> fileData;
    string path = "./" + fileName;
    ifstream inputFile( path, ios::binary );
    char byte_data;

    while( !inputFile.eof() ){
        inputFile.read( &byte_data, 1 );
        fileData.push_back( byte_data );
    }
    fileData.pop_back();
    inputFile.close();

    return fileData;

}

int main() {
    
    auto vec = downloadFile( "file.txt" );
    uploadFile( "outTestFile.txt", vec );

}
