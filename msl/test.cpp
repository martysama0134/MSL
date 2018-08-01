#include <msl/msl.h>

#include <iostream>
#include <string>
using namespace std::string_literals;

int main()
{
	msl::file_ptr p("test.txt");
	std::cout << ((p.is_open()) ? "OPEN"s : "CLOSE"s) << '\n';
	std::cout << p.size() << '\n';
	std::cout << p.string_read() << '\n';
	getchar();
	getchar();
	return 0;
}
