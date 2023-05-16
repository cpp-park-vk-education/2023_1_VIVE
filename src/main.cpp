#include "game.hpp"

#include <iostream>

#include <string>

using namespace std;

int main() {
//    GameEngine::getClient()->connect();
    GameEngine game;
    game.run();
    return 0;
}