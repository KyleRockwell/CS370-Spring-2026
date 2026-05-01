#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

int main(int argc, char *argv[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_RES *res2;
    MYSQL_RES *res3;
    MYSQL_ROW row;
    MYSQL_ROW row2;
    MYSQL_ROW row3;
	
    printf("Content-type: text/html\n\n");
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost",
                            MYSQL_USERNAME,
                            MYSQL_PASSWORD,
                            MYSQL_DATABASE,
                            0, NULL, 0))
    {
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

    if (!res || mysql_num_rows(res) == 0)
    {
        printf("<h1>Not logged in</h1>");
        mysql_close(conn);
        return 0;
    }

    row = mysql_fetch_row(res);
    const int user_id = atoi(row[0]);

    mysql_free_result(res);
    // Query for the names of the User's items
    sprintf(query, "SELECT Items.Item_Name FROM Bids JOIN Auctions ON Bids.Auction_ID = Auctions.Auction_ID JOIN Items ON Items.Item_ID = Auctions.Item_ID JOIN Transactions ON Transactions.Auction_ID = Auctions.Auction_ID WHERE Bidder_ID = %d AND Buyer_ID != %d;", user_id);


    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s can't query db\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Save the name
    res = mysql_store_result(conn);



    if (!res)
    {
        fprintf(stderr, "%s res is null\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

   
    sprintf(query, "SELECT Transactions.Buyer_ID FROM Bids JOIN Auctions ON Bids.Auction_ID = Auctions.Auction_ID JOIN Transactions ON Transactions.Auction_ID = Auctions.Auction_ID WHERE Bidder_ID = %d", user_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s can't query db\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res2 = mysql_store_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        sprintf(query, "SELECT Transactions.Buyer_ID FROM Bids JOIN Auctions ON Bids.Auction_ID = Auctions.Auction_ID JOIN Transactions ON Transactions.Auction_ID = Auctions.Auction_ID WHERE Bidder_ID = %d", user_id);

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s can't query db\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }

        res2 = mysql_store_result(conn);
	row2 = mysql_fetch_row(res2);
        sprintf(query, "SELECT MAX(Bids.Price) FROM Bids JOIN Auctions ON Bids.Auction_ID = Auctions.Auction_ID JOIN Transactions ON Transactions.Auction_ID = Auctions.Auction_ID WHERE Bidder_ID = %s", row2[0]);

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s can't query db\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }

        res3 = mysql_store_result(conn);
	row3 = mysql_fetch_row(res3);
        if (row[0] != NULL)
        {
            std::cout << "<tr><td>" << row[0] << "</td><td>" << row3[0] << "</td></tr>";
        }
    }


    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
