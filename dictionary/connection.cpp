// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "connection.h"

dictionary::connection::connection(boost::asio::io_service & io_service):
	strand_(io_service),
	socket_(io_service)
{
}

boost::asio::ip::tcp::socket & dictionary::connection::socket()
{
	return socket_;
}

void dictionary::connection::start()
{
	auto self = shared_from_this();
	socket_.async_read_some(boost::asio::buffer(buffer_),
		strand_.wrap(
			[this, self](const boost::system::error_code & e, std::size_t bytes_transfered)
			{
				handle_read(e, bytes_transfered);
			}));
}

void dictionary::connection::handle_read(const boost::system::error_code & e, std::size_t bytes_transfered)
{
	if (e)
		return;

	auto self = shared_from_this();
	boost::asio::async_write(socket_, boost::asio::buffer(buffer_, bytes_transfered),
		strand_.wrap(
			[this, self](const boost::system::error_code& e, std::size_t bytes_transfered) {
				handle_write(e, bytes_transfered);
	}));
}

void dictionary::connection::handle_write(const boost::system::error_code & e, std::size_t bytes_transfered)
{
	if (!e)
	{
		// Initiate graceful connection closure
		boost::system::error_code ignored_ec;
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}
}
