#pragma once
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>

namespace dictionary
{
	struct reply;
	struct request;

	class request_handler
	{
	public:
		request_handler();

		void handle_request(const request&, reply& rep);
	private:
		request_handler(const request_handler&) = delete;

		/// Performs url decoding on a string. Retunrs false if the
		/// encoding was invalid
		static bool url_decode(const std::string& in, std::string& out);
	};
}