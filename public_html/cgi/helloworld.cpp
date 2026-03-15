#include <iostream>
#include <string>
void display_html_headers(){

//	std::cout << "Content-type:text/html\r\n\r\n";
//	std::cout << "<html>\n";
//	std::cout << "<head>\n";
//	std::cout << "<title>GBAY-LOGIN</title>\n";
//	std::cout << "</head>\n";
//	std::cout << "<body>\n";
//	std::cout << "<h1> GBAY </h1>\n";
//	std::cout << "</body>\n";	
	//std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<!DOCTYPE html>\n";
	std::cout << "<html>";
	std::cout << "<head>\n";
	std::cout << "<title>Hello World - First CGI Program</title>\n";
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	std::cout << "<h2>Hello world, testing CGI program</h2>/n";
	std::cout << "</body>\n";
	std::cout << "</html>\n";
}
void display_html_footers(){
	std::cout << "</html>\n";
}

void display_html_user(char* user){
	std::cout <<
	       	"<h2> Hello " << user << " you have just logged in successfully </h2> \n";
}

int main (int argc, char *argv[]) {
	char *username;
	char *password;
	//if there are more than two arguments,(unexpected) do something
	if (argc != 2){
		const char* username = "ERROR";		
	}
	else{
		username = argv[1];
		password = argv[2];		
	}
	for(int i = 1; i < argc; i++){
		std::cout<< argv[i] << std::endl;
	}
	//std::cout << username << std::endl;

	display_html_headers();
	//display_html_user(username);
//	display_html_footers();
	return 0;
}
