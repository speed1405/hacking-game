#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace saves {

struct GameState {
    int credits;
    int reputation;
    int level;
    std::string current_act;
};

void save_game(const std::string& filename, const GameState& state);
GameState load_game(const std::string& filename);

} // namespace saves
