#include "SaveSystem.hpp"
#include <fstream>

namespace saves {

void save_game(const std::string& filename, const GameState& state) {
    nlohmann::json j;
    j["credits"] = state.credits;
    j["reputation"] = state.reputation;
    j["level"] = state.level;
    j["current_act"] = state.current_act;

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
    }
}

GameState load_game(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return {0, 0, 1, "Prologue"};

    nlohmann::json j;
    file >> j;
    return {
        j["credits"],
        j["reputation"],
        j["level"],
        j["current_act"]
    };
}

} // namespace saves
