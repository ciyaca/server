#pragma once

#include <vector>
#include <string>

#include "feverrpc/feverrpc-server.hpp"
#include "feverrpc/feverrpc.hpp"
#include "feverrpc/utils.hpp"
#include "feverrpc/feverrpc-factory.hpp"


using namespace std;

int regist ( string username, string password );
int login ( string username, string password );
int joinGroup ( string username, string groupName );
int exitGroup ( string username, string groupName );

extern map<string, FeverRPC::Caller> connections;
