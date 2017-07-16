// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2017 Nemanja Boric (4burgos _at_ _gmail_ _com_)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "server.h"
#include <boost/thread/thread.hpp>

dictionary::Server::Server(const std::string & address, const std::string& port, const std::string & doc_root, std::size_t thread_pool_size):
	thread_pool_size_(thread_pool_size),
	io_service_(),
	acceptor_(io_service_)
{
	// Open the acceptor with the option to reuse the address
	boost::asio::ip::tcp::resolver resolver(io_service_);
	boost::asio::ip::tcp::resolver::query query(address, port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	start_accept();
}

void dictionary::Server::run()
{
	// Create a pool of threads to run allof the io_service
	std::vector<std::shared_ptr<boost::thread>> threads;

	for(std::size_t i = 0; i < thread_pool_size_; i++)
	{
		auto thread = std::make_shared<boost::thread>(
			[this]()
		{
			io_service_.run();
		});
		threads.push_back(thread);
	}

	for (auto& t: threads)
	{
		t->join();
	}
}

void dictionary::Server::start_accept()
{
	new_connection_.reset(new connection(io_service_));
	acceptor_.async_accept(new_connection_->socket(),
		[this](const boost::system::error_code& e) {
		handle_accept(e);
	});
}

void dictionary::Server::handle_accept(const boost::system::error_code & e)
{
	if (!e)
	{
		new_connection_->start();
	}

	start_accept();
}
