#include "game.hpp"

#include <iostream>

#include <string>

using namespace std;

// #include <SFML/Audio.hpp>
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

int main() {
    // sf::SoundBuffer sb;
    // sb.loadFromFile("../assets/sounds/close_attack.wav");
    // sf::Sound sd;
    // sd.setBuffer(sb);

    // int a = 0;
    // std::cin >> a;
    // if (a == 5) {
    //     sd.play();
    //     std::chrono::seconds duration(5);
    //     std::this_thread::sleep_for(duration);
    // }
//    GameEngine::getClient()->connect();
    GameEngine game;
    game.run();
    return 0;
}
