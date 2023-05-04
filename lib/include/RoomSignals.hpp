#pragma once

#include <boost/signals2.hpp>
#include <functional>
#include "SignalManager.hpp"

class RoomSignals;
using RoomSignalsShPtr = std::shared_ptr<RoomSignals>;

class RoomSignals
{
public:
    RoomSignals(const SignalManager& room_manager)
    {
        requestNewRoom.connect(std::bind(&SignalManager::getNewRoom, room_manager));
    }

    boost::signals2::signal<bool()> requestNewRoom;
    boost::signals2::signal<bool(int)> joinRoom;
    boost::signals2::signal<bool()> leaveRoom;
    boost::signals2::signal<void(Message)> askToDeliver;
};