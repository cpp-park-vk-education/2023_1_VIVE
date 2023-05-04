#include "SignalManager.hpp"
#include "Server.hpp"

SignalManager::SignalManager(ServerShPtr server) : server_(server)
{
}

bool SignalManager::getNewRoom()
{
    auto new_room = server_->createNewRoom();

    return new_room != nullptr;
}