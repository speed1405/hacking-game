#pragma once
#include <string>
#include <vector>
#include <map>

namespace hardware {

enum class Era { Copper, Silicon, Cloud };

struct Component {
    std::string name;
    std::string type;
    Era era;
    int performance; // Percentage or multiplier
    int cost;
};

class PC {
public:
    PC();
    bool install(Component comp);
    std::string get_sysinfo() const;
    int get_total_performance() const;

private:
    std::map<std::string, Component> components;
    std::string get_era_name(Era era) const;
};

} // namespace hardware
