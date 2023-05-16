#include "Server.hpp"

SignalManager::SignalManager(ServerShPtr server) : server_(server), room_(nullptr), connection_(nullptr)
{
}

void SignalManager::setConnection(ConnectionShPtr connection)
{
    if (!connection_)
        connection_ = connection;
    else
        std::cerr << "This SignalManager already has connection!" << std::endl;
}

int SignalManager::getNewRoom()
{
    if (!room_)
        room_->leave(connection_);

    auto new_room = server_->createNewRoom();

    if (new_room.first)
    {
        room_ = new_room.first;
        room_->join(connection_);
        return new_room.second;
    }
    else
        return 0;
}

bool SignalManager::joinExistentRoom(int room_id)
{
    if (!room_)
        room_->leave(connection_);

    auto room_to_connect = server_->getRoom(room_id);

    if (room_to_connect)
    {
        room_ = room_to_connect;
        room_->join(connection_);
        return true;
    }
    else
        return false;
}

bool SignalManager::leaveCurrentRoom()
{
    if (!room_)
        return false;

    room_->leave(connection_);
    return true;
}

void SignalManager::deliverToPlayers(const Message& mess)
{
    return;
}