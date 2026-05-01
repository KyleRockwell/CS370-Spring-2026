#include <mysql/mysql.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

char* get_post_data() {
    char *len_str = getenv("CONTENT_LENGTH");
    if (!len_str) return NULL;

    int len = atoi(len_str);
    if (len <= 0) return NULL;

    char *data = (char*)malloc(len + 1);
    fread(data, 1, len, stdin);
    data[len] = '\0';

    return data;
}

void extract_field(char *src, const char *key, char *out) {
    char pattern[64];
    sprintf(pattern, "%s=", key);

    char *pos = strstr(src, pattern);
    if (!pos) {
        out[0] = '\0';
        return;
    }

    pos += strlen(pattern);

    int i = 0;
    while (*pos && *pos != '&') {
        if (*pos == '+') {
            out[i++] = ' ';
        } else {
            out[i++] = *pos;
        }
        pos++;
    }

    out[i] = '\0';
}

int main() {
    printf("Content-type: text/html\n\n");

    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost",
                            MYSQL_USERNAME,
                            MYSQL_PASSWORD,
                            MYSQL_DATABASE,
                            0, NULL, 0)) {
        printf("<h1>DB connection failed</h1>");
        return 1;
    }

    char *cookies = getenv("HTTP_COOKIE");
    if (!cookies) cookies = (char*)"";

    char session_id[256] = "";
    char *pos = strstr(cookies, "session_id=");

    if (!pos) {
        printf("<h1>No session</h1>");
        return 1;
    }

    pos += strlen("session_id=");
    int i = 0;

    while (*pos && *pos != ';') {
        session_id[i++] = *pos++;
    }
    session_id[i] = '\0';

    char query[512];

    sprintf(query,
        "SELECT user_id FROM sessions "
        "WHERE id='%s' AND expires_at > NOW()",
        session_id);

    if (mysql_query(conn, query)) {
        printf("<h1>Session query failed</h1>");
        return 1;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res || mysql_num_rows(res) == 0) {
        printf("<h1>Not logged in</h1>");
        return 1;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int user_id = atoi(row[0]);
    mysql_free_result(res);

    char *post = get_post_data();

    if (!post) {
        printf("<h1>No POST data</h1>");
        return 1;
    }

    char auction_id[32] = "";
    char price_str[32] = "";

    extract_field(post, "auction_id", auction_id);
    extract_field(post, "price", price_str);

    if (strlen(auction_id) == 0 || strlen(price_str) == 0) {
        printf("<h1>Invalid form data</h1>");
        free(post);
        return 1;
    }

    double bid_price = atof(price_str);
    time_t now = time(NULL);

    sprintf(query,
        "SELECT Items.Owner_ID, Auctions.End_Time, Auctions.Start_Price "
        "FROM Auctions "
        "JOIN Items ON Auctions.Item_ID = Items.Item_ID "
        "WHERE Auctions.Auction_ID = %s",
        auction_id);

    if (mysql_query(conn, query)) {
        printf("<h1>Auction query failed</h1>");
        free(post);
        return 1;
    }

    res = mysql_store_result(conn);

    if (!res || mysql_num_rows(res) == 0) {
        printf("<h1>Auction not found</h1>");
        free(post);
        return 1;
    }

    row = mysql_fetch_row(res);

    int owner_id = atoi(row[0]);
    long end_time = atol(row[1]);
    double start_price = atof(row[2]);

    mysql_free_result(res);

    if (owner_id == user_id) {
        printf("<h1>You cannot bid on your own item</h1>");
        free(post);
        return 1;
    }

    if (now >= end_time) {
        printf("<h1>Auction closed</h1>");
        free(post);
        return 1;
    }

    sprintf(query,
        "SELECT MAX(Price) FROM Bids WHERE Auction_ID = %s",
        auction_id);

    if (mysql_query(conn, query)) {
        printf("<h1>Bid lookup failed</h1>");
        free(post);
        return 1;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    double current_price = start_price;

    if (row && row[0]) {
        current_price = atof(row[0]);
    }

    mysql_free_result(res);

    if (bid_price <= current_price) {
        printf("<h1>Bid too low (current: %.2f)</h1>", current_price);
        free(post);
        return 1;
    }

    //Insert bid
    sprintf(query,
        "INSERT INTO Bids (Bidder_ID, Auction_ID, Price, Time_Placed) "
        "VALUES (%d, %s, %f, %ld)",
        user_id, auction_id, bid_price, now);

    if (mysql_query(conn, query)) {
        printf("<h1>Failed to place bid</h1>");
        free(post);
        return 1;
    }

    printf("<h1>Bid placed successfully!</h1>");

    mysql_close(conn);
    free(post);

    return 0;
}        
