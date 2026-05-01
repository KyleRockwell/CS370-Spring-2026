#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <mysql/mysql.h>
#include <ctime>
#include <sstream>
#include <funcs.cpp>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

using namespace std;


// Generate session ID
string generateSessionID()
{
    stringstream ss;
    ss << time(NULL) << rand();
    return ss.str();
}

int main()
{
    // Read POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));

    string postData;

    for(int i = 0; i < content_length; i++)
    {
        char c = getchar();
        postData += c;
    }

    string email = getValue(postData, "email");
    string password = getValue(postData, "password");

    // Connect to MySQL
    MYSQL *conn = mysql_init(NULL);

    if(!mysql_real_connect(conn,
                           "localhost",
                           MYSQL_USERNAME,
                           MYSQL_PASSWORD,
                           MYSQL_DATABASE,
                           0,
                           NULL,
                           0))
    {
        cout << "Content-type: text/html\n\n";
        cout << "<h1>Database connection failed</h1>";
        return 0;
    }

    // Escape input (SQL injection protection)
    char email_escaped[512];
    char password_escaped[512];

    mysql_real_escape_string(conn, email_escaped, email.c_str(), email.length());
    mysql_real_escape_string(conn, password_escaped, password.c_str(), password.length());

    // Query user
    string query =
        "SELECT User_ID, Username FROM Users WHERE Email='" +
        string(email_escaped) +
        "' AND Password='" +
        string(password_escaped) + "'";

    if(mysql_query(conn, query.c_str()))
    {
         cout << "Content-type: text/html\n\n";
         cout << "<h1>Query failed</h1>";
         cout << "<p>" << mysql_error(conn) << "</p>";
         return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;

    if(mysql_num_rows(res) > 0)
    {
        row = mysql_fetch_row(res);

        string user_id = row[0];

        // Create session
        string sessionID = generateSessionID();

        string sessionQuery =
            "INSERT INTO sessions (id, user_id, expires_at) VALUES ('" +
            sessionID + "', " +
            user_id +
            ", NOW() + INTERVAL 5 MINUTE)";

        mysql_query(conn, sessionQuery.c_str());

        // ✅ Correct CGI redirect headers
        cout << "Status: 302 Found\r\n";
        cout << "Set-Cookie: session_id=" << sessionID << "; Path=/\r\n";
        cout << "Location: ../home.html\r\n";
        cout << "\r\n";
    }
    else
    {
        cout << "Content-type: text/html\n\n";
        cout << "<h1>Invalid email or password</h1>";
        cout << "<a href='../login.html'>Try Again</a>";
    }

    mysql_close(conn);
}
