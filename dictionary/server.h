#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include "connection.h"

namespace dictionary
{
	class Server
	{
	public:
		/// Construct the server to listen on the specified TCP address
		/// and port.
		explicit Server(const std::string& address, const std::string& port,
			const std::string& doc_root, std::size_t thread_pool_size);
		
		/// Run the server's io_service loop
		void run();

	private:
		/// disable copying
		Server(const Server& that) = delete;

		/// Initiaate an accept operation
		void start_accept();

		/// Handle completion of an asynchronous accept operation
		void handle_accept(const boost::system::error_code& e);

		/// The number of threads that willc all io_service::run()
		std::size_t thread_pool_size_;

		/// The io_service used to perform asynchrous operations
		boost::asio::io_service io_service_;

		/// Acceptor used to listen for incoming connections.
		boost::asio::ip::tcp::acceptor acceptor_;

		/// The next connection to be accepted
		std::shared_ptr<connection> new_connection_;

		/// The handler for all incoming requests.
		//request_handler request_handler;
	};
}