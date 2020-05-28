#pragma once

#include <vector>
#include <string>

#include "feverrpc/feverrpc-server.hpp"
#include "feverrpc/feverrpc.hpp"
#include "feverrpc/utils.hpp"
#include "feverrpc/feverrpc-factory.hpp"


using namespace std;


class Group {

    public:
        vector<string> members;

    public:
        Group ();
        Group ( string username );
        int addMember ( string username );
        int removeMember ( string username );

};


int regist ( string username, string password );
int login ( string username, string password );
int newGroup ( string username, string groupName );
int joinGroup ( string username, string groupName );
int exitGroup ( string username, string groupName );
int username2userID(string username);
int userID2username(string username);

extern map<string, string> accounts;
extern map<string, FeverRPC::Caller> connections;
extern map<string, Group> groups;
