#include <iostream>
#include <string>
#include <cstdlib>
#include <mysql/mysql.h>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

using namespace std;

// Extract cookie value
string getCookieValue(string cookies, string key)
{
size_t start = cookies.find(key + "=");

if(start == string::npos)
    return "";

start += key.length() + 1;

size_t end = cookies.find(";", start);

if(end == string::npos)
    return cookies.substr(start);

return cookies.substr(start, end - start);

}

int main()
{
cout << "Content-type: text/plain\n\n";

// Get cookies from environment
char* cookieEnv = getenv("HTTP_COOKIE");

if(cookieEnv == NULL)
{
    cout << "INVALID";
    return 0;
}

string cookies = cookieEnv;

string session_id = getCookieValue(cookies, "session_id");

if(session_id == "")
{
    cout << "INVALID";
    return 0;
}

// Connect to DB
MYSQL *conn = mysql_init(NULL);

mysql_real_connect(conn,
                   "localhost",
                   MYSQL_USERNAME,
                   MYSQL_PASSWORD,
                   MYSQL_DATABASE,
                   0,
                   NULL,
                   0);

// 🔐 Escape session_id
char session_escaped[512];
mysql_real_escape_string(conn, session_escaped, session_id.c_str(), session_id.length());

// Check session validity
string query =
    "SELECT id FROM sessions WHERE id='" +
    string(session_escaped) +
    "' AND expires_at > NOW()";

mysql_query(conn, query.c_str());

MYSQL_RES *res = mysql_store_result(conn);

if(mysql_num_rows(res) > 0)
{
    cout << "VALID";
}
else
{
    cout << "INVALID";
}

mysql_close(conn);

}
