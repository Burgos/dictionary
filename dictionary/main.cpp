#include "server.h"
#include <iostream>

int main()
{
	try
	{
		dictionary::Server s("127.0.0.1", "8080",
			"", 10);
		s.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}