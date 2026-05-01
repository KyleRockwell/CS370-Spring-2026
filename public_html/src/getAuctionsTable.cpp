#include <mysql/mysql.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

int main() {
    printf("Content-type: text/html\n\n");

    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost",
                            MYSQL_USERNAME,
                            MYSQL_PASSWORD,
                            MYSQL_DATABASE,
                            0, NULL, 0)) {
        return 1;
    }

    // =========================
    // SESSION → USER ID
    // =========================
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

    char query[1024];

    sprintf(query,
        "SELECT user_id FROM sessions "
        "WHERE id='%s' AND expires_at > NOW()",
        session_id);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        return 1;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res || mysql_num_rows(res) == 0) {
        mysql_close(conn);
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int user_id = atoi(row[0]);
    mysql_free_result(res);

    // =========================
    // GET OPEN AUCTIONS
    // =========================
    sprintf(query,
        "SELECT Auctions.Auction_ID, Items.Item_Name, Items.Owner_ID, Auctions.End_Time, Items.Item_Desc "
        "FROM Auctions "
        "JOIN Items ON Auctions.Item_ID = Items.Item_ID");

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);

    if (!res) {
        mysql_close(conn);
        return 1;
    }

    time_t now = time(NULL);

    // =========================
    // OUTPUT OPTIONS
    // =========================
    std::string desc;
    while ((row = mysql_fetch_row(res)) != NULL) {

        int auction_id = atoi(row[0]);
        std::string item_name = row[1];
        int owner_id = atoi(row[2]);
        long end_time = atol(row[3]);
	if(row[4] == NULL) 
		desc = "NULL";
	else
		desc = row[4];

        // only show active auctions
        if (now < end_time) {

            if (owner_id != user_id && row[4]) {
		std::cout << "<tr><td>" << item_name << "</td><td>" << desc << "</td><td><input type=\"number\" id=\"quantity\" name=\"quantity\" min=\"0\"><td></tr>";
            }
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
