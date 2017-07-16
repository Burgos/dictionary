#pragma once
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <memory>
#include <array>
#include <boost/asio.hpp>

namespace dictionary
{
	class connection:
		public std::enable_shared_from_this<connection>
	{
	public:
		explicit connection(boost::asio::io_service& io_service);

		/// Get the socket associated with the connection
		boost::asio::ip::tcp::socket& socket();

		/// Start the first async operation for the connection
		void start();

	private:
		/// Handle completiono of a read operation
		void handle_read(const boost::system::error_code& e,
			std::size_t bytes_transfered);

		/// Handle completion of a write operation
		void handle_write(const boost::system::error_code & e, std::size_t bytes_transfered);

		/// Strand to ensure the connection's handlers are not called
		/// concurently
		boost::asio::io_service::strand strand_;

		/// Socket
		boost::asio::ip::tcp::socket socket_;

		/// Buffer for the incoming data
		std::array<char, 8192> buffer_;

		connection(const connection&) = delete;
	};
}