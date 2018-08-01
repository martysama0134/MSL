#include <msl/msl.h>

int main()
{
	msl::file_ptr p("test.txt");
	puts((p.is_open()) ? "OPEN" : "CLOSE");
	{
		char buf[100]{};
		fread(buf, 1, sizeof buf, *p);
		puts(buf);
	}
	getchar();
	getchar();
	return 0;
}
