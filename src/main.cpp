#include <iostream>
#include "Server.hpp"

int main(int argc, char* argv[])
{
    /*boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), 8080);
    Server s(io_context, endpoint);
    io_context.run();*/
    std::cout << "Hello, World!" << std::endl;
    return 0;
}