#pragma once
#include <string>
#include <vector>
#include <memory>
#include "VFS.hpp"
#include "Network.hpp"
#include "Hardware.hpp"
#include "Missions.hpp"

namespace shell {

class Shell {
public:
    Shell(std::shared_ptr<vfs::FileSystem> fs,
          std::shared_ptr<network::Network> net,
          std::shared_ptr<hardware::PC> pc,
          std::shared_ptr<missions::MissionManager> mm);
    std::string execute(const std::string& input);
    std::string get_prompt() const;

private:
    std::shared_ptr<vfs::FileSystem> fs;
    std::shared_ptr<network::Network> net;
    std::shared_ptr<hardware::PC> pc;
    std::shared_ptr<missions::MissionManager> mm;
    std::shared_ptr<network::Host> connected_host;

    int credits = 0;
    int reputation = 0;
    int level = 1;

    std::string user = "user";
    std::string hostname = "localhost";

    std::vector<std::string> tokenize(const std::string& input);
};

} // namespace shell
