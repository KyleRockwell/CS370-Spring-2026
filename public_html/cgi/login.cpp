#include <iostream>
void display_html_header(){

	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<title>G-Bay Login</title>\n";
	std::cout << "</head>\n";
}
void display_html_footer(){

	std::cout << "<body>\n";
	std::cout << "<h2>Hello world, testing CGI program</h2>/n";
	std::cout << "</body>\n";
	std::cout << "</html>\n";
}
int main () {
	display_html_header();
	display_html_footer();
	return 0;
}
