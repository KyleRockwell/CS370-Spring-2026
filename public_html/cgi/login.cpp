#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
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

    string query =
        "SELECT username FROM Users WHERE email='" +
        email +
        "' AND password='" +
        password +
        "'";

    mysql_query(conn, query.c_str());

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;

    if(mysql_num_rows(res) > 0)
    {
        row = mysql_fetch_row(res);

        string username = row[0];

        cout << "<!DOCTYPE html>";
        cout << "<html>";
        cout << "<head><title>G-Bay Portal</title></head>";
        cout << "<body>";

        cout << "<h1>Welcome, " << username << "</h1>";

        cout << "<a href='/~teamg/index.html'>Logout</a>";

        cout << "</body>";
        cout << "</html>";
    }
    else
    {
        cout << "<h1>Invalid email or password</h1>";
        cout << "<a href='/~teamg/login.html'>Try Again</a>";
    }

    mysql_close(conn);

}
