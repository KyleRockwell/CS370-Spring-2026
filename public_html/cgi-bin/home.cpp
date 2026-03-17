#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
using namespace std;

string getValue(string data, string key)
{
    size_t start = data.find(key + "=");
    if(start == string::npos) return "";

    start += key.length() + 1;

    size_t end = data.find("&", start);

    if(end == string::npos)
        return data.substr(start);

    return data.substr(start, end - start);
}

int main()
{
    cout << "Content-type: text/html\n\n";

    string query = getenv("QUERY_STRING");

    string username = getValue(query, "username");

    cout << "<html>";
    cout << "<head><title>G-Bay Home</title></head>";
    cout << "<body>";

    cout << "<h1>Welcome, " << username << "!</h1>";

    cout << "<p>This is your user dashboard.</p>";

    cout << "<a href='/~teamg/index.html'>Logout</a>";

    cout << "</body>";
    cout << "</html>";

    for(int time = 0; time <= 5; time++) { //Counter for auto-timeout
        sleep(1);
    }
    cout << "time is UP";
}
