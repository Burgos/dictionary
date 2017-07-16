// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <boost/logic/tribool.hpp>
#include <tuple>
#include "request.h"

namespace dictionary
{
	class request_parser
	{
	public:
		/// construct ready to parse the request method
		request_parser();

		/// Reset to inintal parser state.
		void reset();

		/// Parse some data. The tribool return value is true when
		/// a complete request has been parsed, false if the data is
		/// invalid, indeterminate when more data is required. The
		/// InputIterator return value indicated how much of the
		/// data has been consumed.
		template <typename InputIterator>
		std::tuple<boost::tribool, InputIterator> parse(request& req,
			InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				auto result = consume(req, *begin++);
				if (result || !result)
					return std::make_tuple(result, begin);
			}

			return std::make_tuple(boost::indeterminate, begin);
		}

	private:
		// Handle the next character of input
		boost::tribool consume(request& req, char input);

		/// Check if a byte is an HTTP character
		static bool is_char(int c);

		/// Check if a byte is an HTTP control character
		static bool is_ctl(int c);

		/// Check if a byte is defined as an HTTP tspecial character.
		static bool is_tspecial(int c);

		/// Check if a byte is a digit
		static bool is_digit(int c);

		/// The current state of the parser
		enum state
		{
			method_start,
			method,
			uri,
			http_version_h,
			http_version_t_1,
			http_version_t_2,
			http_version_p,
			http_version_slash,
			http_version_major_start,
			http_version_major,
			http_version_minor_start,
			http_version_minor,
			expecting_newline_1,
			header_line_start,
			header_lws,
			header_name,
			space_before_header_value,
			header_value,
			expecting_newline_2,
			expecting_newline_3
		} state_;
	};
}