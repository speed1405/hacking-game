#include "Missions.hpp"
#include <random>

namespace missions {

void MissionManager::add_mission(Mission m) {
    story_missions.push_back(m);
}

std::vector<Mission> MissionManager::get_available_missions() const {
    return story_missions;
}

Mission* MissionManager::get_mission(const std::string& id) {
    for (auto& m : story_missions) {
        if (m.id == id) return &m;
    }
    return nullptr;
}

Mission MissionManager::generate_procedural(int level) {
    // Basic random generation
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 500);

    return {
        "PROC-" + std::to_string(dis(gen)),
        "Random Data Recovery",
        "A client needs data from a remote server.",
        "555-" + std::to_string(dis(gen)),
        level * 100,
        level * 10,
        false
    };
}

} // namespace missions
