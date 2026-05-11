#include "Shell.hpp"
#include <sstream>
#include <iterator>

namespace shell {

Shell::Shell(std::shared_ptr<vfs::FileSystem> fs,
             std::shared_ptr<network::Network> net,
             std::shared_ptr<hardware::PC> pc,
             std::shared_ptr<missions::MissionManager> mm)
    : fs(fs), net(net), pc(pc), mm(mm) {}

std::vector<std::string> Shell::tokenize(const std::string& input) {
    std::istringstream iss(input);
    return {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
}

std::string Shell::get_prompt() const {
    return user + "@" + hostname + ":~$ ";
}

std::string Shell::execute(const std::string& input) {
    auto tokens = tokenize(input);
    if (tokens.empty()) return "";

    std::string cmd = tokens[0];

    // Commands that work differently when connected
    auto active_fs = connected_host ? connected_host->get_fs() : fs;

    if (cmd == "ls") {
        auto items = active_fs->ls();
        std::string output;
        for (const auto& item : items) output += item + "  ";
        return output;
    } else if (cmd == "cat") {
        if (tokens.size() > 1) {
            auto node = active_fs->get_node(tokens[1]);
            if (node && node->type == vfs::NodeType::File) {
                return node->content;
            }
            return "cat: " + tokens[1] + ": No such file or directory";
        }
        return "cat: missing operand";
    } else if (cmd == "dial") {
        if (tokens.size() > 1) {
            auto host = net->find_host(tokens[1]);
            if (host) {
                connected_host = host;
                hostname = host->get_hostname();
                return "Connecting to " + tokens[1] + "... Connected.";
            }
            return "Failed to connect: No carrier";
        }
        return "dial: missing address";
    } else if (cmd == "scan") {
        if (connected_host) {
            std::string output = "Scanning " + connected_host->get_ip() + "...\n";
            for (const auto& svc : connected_host->get_services()) {
                output += std::to_string(svc.port) + "/tcp open  " + svc.name + " " + svc.version + "\n";
            }
            return output;
        }
        return "Not connected to any host";
    } else if (cmd == "exit") {
        if (connected_host) {
            connected_host = nullptr;
            hostname = "localhost";
            return "Connection closed.";
        }
        return "logout";
    } else if (cmd == "sysinfo") {
        return pc->get_sysinfo();
    } else if (cmd == "stats") {
        return "Level: " + std::to_string(level) + " | Rep: " + std::to_string(reputation) + " | Credits: " + std::to_string(credits);
    } else if (cmd == "missions") {
        auto avail = mm->get_available_missions();
        std::string output = "--- Available Missions ---\n";
        for (const auto& m : avail) {
            output += "[" + m.id + "] " + m.title + " (" + std::to_string(m.credit_reward) + "c)\n";
        }
        return output;
    } else if (cmd == "mkdir") {
        if (tokens.size() > 1) {
            active_fs->mkdir(tokens[1]);
            return "";
        }
        return "mkdir: missing operand";
    } else if (cmd == "help") {
        return "Available commands: ls, cat, mkdir, dial, scan, sysinfo, stats, missions, exit, help, clear";
    } else if (cmd == "clear") {
        return "__CLEAR__";
    }

    return cmd + ": command not found";
}

} // namespace shell
