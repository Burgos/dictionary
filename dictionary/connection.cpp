#include "connection.h"

#include <boost/bind.hpp>


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
	socket_.async_read_some(boost::asio::buffer(buffer_),
		strand_.wrap(
			boost::bind(&connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)));
}

void dictionary::connection::handle_read(const boost::system::error_code & e, std::size_t bytes_transfered)
{
	if (e)
		return;

	boost::asio::async_write(socket_, boost::asio::buffer(buffer_, bytes_transfered),
		boost::bind(&connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
}

void dictionary::connection::handle_write(const boost::system::error_code & e)
{
	if (!e)
	{
		// Initiate graceful connection closure
		boost::system::error_code ignored_ec;
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}
}
