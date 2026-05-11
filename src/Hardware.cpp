#include "Hardware.hpp"
#include <sstream>

namespace hardware {

PC::PC() {
    // Basic Copper-era starter parts
    components["CPU"] = {"80386", "CPU", Era::Copper, 100, 0};
    components["RAM"] = {"4MB SIMM", "RAM", Era::Copper, 100, 0};
    components["MODEM"] = {"2400 Baud", "MODEM", Era::Copper, 10, 0};
    components["HDD"] = {"40MB IDE", "HDD", Era::Copper, 40, 0};
}

bool PC::install(Component comp) {
    // Simplified compatibility check: Motherboard (Implicitly the current era)
    // For now, just replace
    components[comp.type] = comp;
    return true;
}

std::string PC::get_era_name(Era era) const {
    switch (era) {
        case Era::Copper: return "Copper (1990s)";
        case Era::Silicon: return "Silicon (2000s)";
        case Era::Cloud: return "Cloud (Modern)";
    }
    return "Unknown";
}

std::string PC::get_sysinfo() const {
    std::stringstream ss;
    ss << "     .---.          \n"
       << "    /     \\         USER: user@localhost\n"
       << "    | (O) |         ERA:  " << get_era_name(Era::Copper) << "\n"
       << "    \\     /         --------------------\n"
       << "     '---'          CPU:  " << components.at("CPU").name << "\n"
       << "    /     \\         RAM:  " << components.at("RAM").name << "\n"
       << "   |       |        NET:  " << components.at("MODEM").name << "\n"
       << "   '-------'        DISK: " << components.at("HDD").name << "\n";
    return ss.str();
}

int PC::get_total_performance() const {
    int total = 0;
    for (const auto& [type, comp] : components) total += comp.performance;
    return total;
}

} // namespace hardware
