#include <chrono>
#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>
#include "funcs.cpp"

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

using namespace std;

// Currently compiling with -ggdb for gdb debugging
int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	string postData;
	std::cout<<"getenv:" << atoi(getenv("CONTENT_LENGTH")) << std::endl;
	int content_length = atoi(getenv("CONTENT_LENGTH"));   //segfault here, part of "getenv" I think
	for(int i = 0; i < content_length; i++) {
		char c = getchar();
		postData += c;
	}
/*
	cout << "Content-type: text/html";
	string name = getValue(postData, "item_name");
	string desc = getValue(postData, "item_desc"); 
	string price = getValue(postData, "Start_Price");
	
	if (!mysql_real_connect(conn, "localhost", MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
		fprintf(stderr, "%s can't connect to db\n", mysql_error(conn));
		return 1;
	} 

    char *cookies = getenv("HTTP_COOKIE");
    if (!cookies)
        cookies = (char*)"";

    char session_id[256] = "";

    char *pos = strstr(cookies, "session_id=");
    if (pos)
    {
        pos += strlen("session_id=");

        int i = 0;
        while (*pos && *pos != ';' && i < 255)
        {
            session_id[i++] = *pos++;
        }
        session_id[i] = '\0';
    }

    char query[512];

    sprintf(query,
            "SELECT user_id FROM sessions "
            "WHERE id='%s' AND expires_at > NOW()",
            session_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s can't query session\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);


    row = mysql_fetch_row(res);
    const int user_id = atoi(row[0]);

    mysql_free_result(res);

    sprintf(query, "INSERT INTO Items (Owner_ID, Item_Name, Item_Desc) VALUES (%d, \"%s\", \"%s\");", user_id, name, desc);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query database\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    sprintf(query, "SELECT MAX(Items.Item_ID) FROM Items WHERE Owner_ID = %d;", user_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query database\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    sprintf(query, "INSERT INTO Auctions (Item_ID, Start_Price, Start_Time, End_Time) VALUES (%d, %d, %d, %d);", row[0], price, (long)time(nullptr), (long)time(nullptr) + 86400);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query database\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
	 
    mysql_free_result(res);
    mysql_close(conn);
*/
    cout << "Successfully submitted";
    return 0; 
}
