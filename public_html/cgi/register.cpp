#include <iostream>
#include <string>
#include <cstdlib>
#include <mysql/mysql.h>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

using namespace std;

string getValue(string data, string key)
{
    size_t start = data.find(key + "=");

    if(start == string::npos)
        return "";

    start += key.length() + 1;

    size_t end = data.find("&", start);

    if(end == string::npos)
        return data.substr(start);

    return data.substr(start, end - start);
}

int main()
{
    cout << "Content-type: text/html\n\n";

    int content_length = atoi(getenv("CONTENT_LENGTH"));

    string postData;

    for(int i = 0; i < content_length; i++)
    {
        char c = getchar();
        postData += c;
    }

    string username = getValue(postData, "username");
    string email = getValue(postData, "email");
    string password = getValue(postData, "password");

    MYSQL *conn = mysql_init(NULL);

    mysql_real_connect(conn,
                       "localhost",
                       MYSQL_USERNAME,
                       MYSQL_PASSWORD,
                       MYSQL_DATABASE,
                       0,
                       NULL,
                       0);

    string checkQuery =
        "SELECT email FROM Users WHERE email='" + email + "'";

    mysql_query(conn, checkQuery.c_str());

    MYSQL_RES *res = mysql_store_result(conn);

    if(mysql_num_rows(res) > 0)
    {
        cout << "<h1>Email already registered</h1>";
        cout << "<a href='/~teamg/register.html'>Try again</a>";
        return 0;
    }

    string insertQuery =
        "INSERT INTO Users (username,email,password) VALUES ('" +
        username + "','" + email + "','" + password + "')";

    mysql_query(conn, insertQuery.c_str());

    cout << "<h1>Registration successful</h1>";
    cout << "<a href='/~teamg/login.html'>Login</a>";

    mysql_close(conn);
}
