// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
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