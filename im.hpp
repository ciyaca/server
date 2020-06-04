#pragma once


int sendMessage ( string sourceName, string targetName, string message, int flag=0 );
int sendFile( string sourceName, string targetName, string fileName, vector<char> fileData, int flag=0 );
int checkHistoryMessage( string username );