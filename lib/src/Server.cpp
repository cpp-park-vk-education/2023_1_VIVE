#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint) : acceptor_(io_context, endpoint)
{
    doAccept();
}

void Server::doAccept()
{
    boost::asio::io_context io_context;
    tcp::socket socket_(io_context);
    free_connections.insert(std::make_shared<Connection>(25, std::move(socket_), std::make_unique<SignalManager>(shared_from_this())));
}

RoomShPtr Server::createNewRoom()
{
    RoomShPtr new_room = std::make_shared<SessionRoom>();
    //id2room.insert(1, new_room);

    return new_room;
}

RoomShPtr Server::getRoom(int room_id)
{
    return id2room.find(1)->second;
}