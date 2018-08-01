#include <msl/msl.h>

#include <iostream>
#include <string>
using namespace std::string_literals;

int main()
{
	msl::file_ptr p("test.txt");
	std::cout << ((p.is_open()) ? "OPEN"s : "CLOSE"s) << '\n';
	std::cout << p.size() << '\n';
	{
		char buf[100]{};
		fread(buf, 1, sizeof buf, *p);
		puts(buf);
	}
	getchar();
	getchar();
	return 0;
}
