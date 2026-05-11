#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Network.hpp"

namespace missions {

struct Mission {
    std::string id;
    std::string title;
    std::string description;
    std::string target_address;
    int credit_reward;
    int rep_reward;
    bool completed = false;
};

class MissionManager {
public:
    void add_mission(Mission m);
    std::vector<Mission> get_available_missions() const;
    Mission* get_mission(const std::string& id);

    // Procedural generation
    Mission generate_procedural(int level);

private:
    std::vector<Mission> story_missions;
};

} // namespace missions
