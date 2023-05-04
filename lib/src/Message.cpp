#include "Message.hpp"

Message::Message(const std::string& mess) : data(mess), body_length(mess.size() - 4)
{

}