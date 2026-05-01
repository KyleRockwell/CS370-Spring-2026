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

// ESCAPE USER INPUT (SQL INJECTION PROTECTION)
char username_escaped[512];
char email_escaped[512];
char password_escaped[512];

mysql_real_escape_string(conn, username_escaped, username.c_str(), username.length());
mysql_real_escape_string(conn, email_escaped, email.c_str(), email.length());
mysql_real_escape_string(conn, password_escaped, password.c_str(), password.length());

// CHECK IF EMAIL EXISTS
string checkQuery =
    "SELECT email FROM Users WHERE email='" + string(email_escaped) + "'";

mysql_query(conn, checkQuery.c_str());

MYSQL_RES *res = mysql_store_result(conn);

if(mysql_num_rows(res) > 0)
{
    cout << "<h1>Email already registered</h1>";
    cout << "<a href='../register.html'>Try again</a>";
    return 0;
}

// INSERT NEW USER
string insertQuery =
    "INSERT INTO Users (username,email,password) VALUES ('" +
    string(username_escaped) + "','" +
    string(email_escaped) + "','" +
    string(password_escaped) + "')";

mysql_query(conn, insertQuery.c_str());

cout << "<h1>Registration successful</h1>";
cout << "<a href='../login.html'>Login</a>";

mysql_close(conn);


}
