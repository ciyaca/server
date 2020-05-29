#include "sql.hpp"


using namespace std;


MYSQL ciyacaSQL;


int ciyacaSqlInit() {

    mysql_init( &ciyacaSQL );

    if( mysql_real_connect( &ciyacaSQL, "127.0.0.1", "root", "124901", "ciyaca", 0, NULL, CLIENT_FOUND_ROWS ) ) {
        cout << "Connect to ciyaca SQL successfully!" << endl;
        return 1;
    } else {
        cout << "Failed to connect to ciyaca SQL!" << endl;
        return -1;
    }

}

int username2userID( string username ){

    string temp = "NULL";
    string queryStr="SELECT userid FROM user WHERE user_name = "+username+";";
    mysql_query( &ciyacaSQL, queryStr.c_str() );
    res_ptr = mysql_store_result(connect);
     if(res_ptr!=NULL)
     {
          result_row = mysql_fetch_row(res_ptr);
            if(result_row!=NULL)
            {
                temp = result_row[0];
            }
            mysql_free_result(res_ptr);
     }
     else{
            //查询结果空
            return 0; 
        }
    int num=atoi(temp.c_str());
    return num;
    
}

int userID2username( string userid ){

    string temp = "NULL";
    string queryStr="SELECT user_name FROM user WHERE userid = "+userid+";";
    mysql_query( &ciyacaSQL, queryStr.c_str() );
    res_ptr = mysql_store_result(connect);
     if(res_ptr!=NULL)
     {
          result_row = mysql_fetch_row(res_ptr);
            if(result_row!=NULL)
            {
                temp = result_row[0];
            }
            mysql_free_result(res_ptr);
     }
     else{
            //查询结果空
            return 0; 
        }
    int num=atoi(temp.c_str());
    return num;

}