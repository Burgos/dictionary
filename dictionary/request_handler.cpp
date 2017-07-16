// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "request_handler.h"
#include <sstream>

dictionary::request_handler::request_handler()
{
}

void dictionary::request_handler::handle_request(const request &, reply & rep)
{
	
}

bool dictionary::request_handler::url_decode(const std::string & in, std::string & out)
{
	out.clear();
	out.reserve(in.size());

	for (std::size_t i = 0; i < in.size(); i++)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else
		{
			out += in[i];
		}
	}

	return true;
}
