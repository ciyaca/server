#pragma once

#include <vector>
#include <string>

#include "feverrpc/feverrpc-server.hpp"
#include "feverrpc/feverrpc.hpp"
#include "feverrpc/utils.hpp"
#include "feverrpc/feverrpc-factory.hpp"


using namespace std;


class Account {

    public:
        string username;
        string password;

    public:
        Account( string _username, string _password );

};


class Connection {

    public:
        string username;
        FeverRPC::Caller caller;

    public:
        Connection( string _username, FeverRPC::Caller _caller );

};


class Group {

    public:
        string groupName;
        vector<Connection> groupMembers;

    public:
        Group( string _groupName );
        int addMember( string username );
        int removeMember( string username );

};


int regist ( string username, string password );
int login ( string username, string password );
int newGroup ( string username, string groupName );
int joinGroup ( string username, string groupName );
int exitGroup ( string username, string groupName );


extern vector<Account> accounts;
extern vector<Connection> connections;
extern vector<Group> groups;
