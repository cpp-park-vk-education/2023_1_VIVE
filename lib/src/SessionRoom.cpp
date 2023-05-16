#include "SessionRoom.hpp"
#include "JSONSerializer.hpp"

SessionRoom::SessionRoom()
{
}

void SessionRoom::join(const ConnectionShPtr new_participant)
{
    participants.insert(new_participant);
}

void SessionRoom::leave(const ConnectionShPtr participant_to_leave)
{
    participants.erase(participant_to_leave);
}

void SessionRoom::deliver(const response::Response& resp)
{
    for (auto participant: participants_)
        participant->deliver(resp);
}