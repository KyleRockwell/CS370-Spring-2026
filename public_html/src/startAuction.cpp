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

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    string postData;

    char* len_str = getenv("CONTENT_LENGTH");
    int content_length = len_str ? atoi(len_str) : 0;

    for(int i = 0; i < content_length; i++) {
        char c = getchar();
        postData += c;
    }

    cout << "Content-type: text/html\r\n\r\n";

    string name = getValue(postData, "item_name");
    string desc = getValue(postData, "item_desc");
    string price = getValue(postData, "start_price");

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s can't connect to db\n", mysql_error(conn));
        return 1;
    }

    char *cookies = getenv("HTTP_COOKIE");
    if (!cookies) cookies = (char*)"";

    char session_id[256] = "";

    char *pos = strstr(cookies, "session_id=");
    if (pos) {
        pos += strlen("session_id=");
        int i = 0;
        while (*pos && *pos != ';' && i < 255) {
            session_id[i++] = *pos++;
        }
        session_id[i] = '\0';
    }

    char query[512];

    // SESSION QUERY
    snprintf(query, sizeof(query),
        "SELECT user_id FROM sessions WHERE id='%s' AND expires_at > NOW()",
        session_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query session\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);
    if (!res) {
        mysql_close(conn);
        return 1;
    }

    row = mysql_fetch_row(res);
    if (!row) {
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    int user_id = atoi(row[0]);
    mysql_free_result(res);

    // INSERT ITEM
    snprintf(query, sizeof(query),
        "INSERT INTO Items (Owner_ID, Item_Name, Item_Desc) VALUES (%d, \"%s\", \"%s\");",
        user_id, name.c_str(), desc.c_str());

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query database\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    int item_id = mysql_insert_id(conn);

    int start_price = atoi(price.c_str());

    // INSERT AUCTION
    snprintf(query, sizeof(query),
        "INSERT INTO Auctions (Item_ID, Start_Price, Start_Time, End_Time) VALUES (%d, %d, %ld, %ld);",
        item_id,
        start_price,
        (long)time(nullptr),
        (long)time(nullptr) + 604800);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s can't query database\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    cout << "<html><div>Successfully submitted</div>";
    cout << "<a href=\"../home.html\">Go gack home</a>";
    return 0;
}
