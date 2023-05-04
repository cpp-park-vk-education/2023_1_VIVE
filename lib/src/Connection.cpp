#include "Connection.hpp"

Connection::Connection(int user_id, tcp::socket socket, SignalManagerShPtr room_manager) : user_id_(user_id), socket_(std::move(socket)), room_manager_(room_manager), room_actions(std::make_shared<RoomSignals>(*room_manager))
{
}