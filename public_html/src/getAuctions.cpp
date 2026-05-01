#include <mysql/mysql.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

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

    char query[512];

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
        "SELECT Auctions.Auction_ID, Items.Item_Name, Items.Owner_ID, Auctions.End_Time "
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
    while ((row = mysql_fetch_row(res)) != NULL) {

        int auction_id = atoi(row[0]);
        const char *item_name = row[1];
        int owner_id = atoi(row[2]);
        long end_time = atol(row[3]);

        // only show active auctions
        if (now < end_time) {

            // OPTIONAL RULE: hide own items
            if (owner_id != user_id) {
                printf("<option value=\"%d\">%s</option>\n",
                       auction_id,
                       item_name);
            }
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
