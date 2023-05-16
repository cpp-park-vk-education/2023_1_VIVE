#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "boost/asio.hpp"

#include "client_connection.hpp"

TEST(MyTest, test_async_connect)
{
    boost::asio::io_context client_io, server_io;
    tcp::resolver resolver(client_io);
    auto endpoints = resolver.resolve("localhost", "5555");

    ClientConnection client(client_io, endpoints);
//    Server server(server_io);

    EXPECT_FALSE(client.connected());
//    EXPECT_EQ(server.clients_count(), 0);
//    server.start_accept();
    client.async_connect("localhost", 5555);

    server_io.run_one();
//    EXPECT_EQ(server.clients_count(), 1);
    EXPECT_FALSE(client.connected());
    client_io.run_one();
    EXPECT_TRUE(client.connected());
}
