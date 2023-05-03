#include <iostream>
#include <thread>
#include "server.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    Server server(5555);
    server.run();
    return 0;
}
