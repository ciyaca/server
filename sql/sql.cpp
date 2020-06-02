#include "sql.hpp"


using namespace std;


MYSQL ciyacaSQL;


int ciyacaSqlInit() {

    mysql_init( &ciyacaSQL );

    if( mysql_real_connect( &ciyacaSQL, "127.0.0.1", "root", "password", "ciyacaSQL", 0, NULL, CLIENT_FOUND_ROWS ) ) {
        cout << "Connect to ciyaca SQL successfully!" << endl;
        return 1;
    } else {
        cout << "Failed to connect to ciyaca SQL!" << endl;
        return -1;
    }

}
