#pragma once

#include <vector>
#include <string>

class SaveManager {
public:
    void loadGame(std::string file_path);
    void saveGame(std::string file_path);
    std::vector<std::string> getSaves();

private:
    std::vector<std::string> saves_;
};
