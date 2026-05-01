
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <mysql/mysql.h>
#include <ctime>
#include <sstream>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

using namespace std;

// Extract value from POST data
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

