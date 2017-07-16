#pragma once

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