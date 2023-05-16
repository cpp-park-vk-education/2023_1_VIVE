#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint) : acceptor_(io_context, endpoint), highest_room_id(0)
{
    doAccept();
}

void Server::doAccept()
{
    std::cout << "Waiting for connection..." << std::endl;
    acceptor_.async_accept
    (
        [this](boost::system::error_code error, tcp::socket socket)
        {
            if (!error)
            {
                std::cout << "Connected" << std::endl;
                auto new_connection = std::make_shared<Connection>(std::move(socket), std::make_unique<SignalManager>(shared_from_this()));
                free_connections.insert(new_connection);
                new_connection->start();
            }
            else
                std::cerr << "Connection failed: " << error.message() << std::endl;

            doAccept();
        }
    );
}

std::pair<RoomShPtr, int> Server::createNewRoom()
{
    RoomShPtr new_room = std::make_shared<SessionRoom>();
    id2room.insert(std::make_pair(++highest_room_id, new_room));

    return std::make_pair(new_room, highest_room_id);
}

RoomShPtr Server::getRoom(int room_id)
{
    return id2room.find(room_id)->second;
}