#pragma once

#include "Message.hpp"

class SessionRoom;
using RoomShPtr = std::shared_ptr<SessionRoom>;

class Server;
using ServerShPtr = std::shared_ptr<Server>;

class SignalManager;
using SignalManagerShPtr = std::shared_ptr<SignalManager>;

class SignalManager
{
private:
    ServerShPtr server_;
    RoomShPtr room_;

public:
    SignalManager(ServerShPtr server);

    bool getNewRoom();
    bool joinExistentRoom(int room_id);
    bool leaveCurrentRoom();
    void deliverToPlayers(const Message& mess);
};