default:
	g++ login.cpp `mysql_config --include` `mysql_config --libs` -o ../cgi-bin/login.cgi
	g++ home.cpp -o ../cgi-bin/home.cgi
	g++ register.cpp `mysql_config --include` `mysql_config --libs` -o ../cgi-bin/register.cgi

clean:
	rm ../cgi-bin/*.cgi
