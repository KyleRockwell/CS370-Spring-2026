#include <iostream>
#include <unistd.h>


int main() { 
	
	char *homeDir = getenv("HOME");

	
		
	std::cout<< homeDir << std::endl;
}
