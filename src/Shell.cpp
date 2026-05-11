#include "Shell.hpp"
#include <sstream>
#include <iterator>

namespace shell {

Shell::Shell(std::shared_ptr<vfs::FileSystem> fs,
             std::shared_ptr<network::Network> net,
             std::shared_ptr<hardware::PC> pc,
             std::shared_ptr<missions::MissionManager> mm,
             std::shared_ptr<exploits::ToolManager> tm)
    : fs(fs), net(net), pc(pc), mm(mm), tm(tm) {}

std::vector<std::string> Shell::tokenize(const std::string& input) {
    std::istringstream iss(input);
    return {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
}

std::string Shell::get_prompt() const {
    auto active_fs = connected_host ? connected_host->get_fs() : fs;
    return user + "@" + hostname + ":" + active_fs->pwd() + "$ ";
}

std::string Shell::execute(const std::string& input) {
    // Redirection support (>, >>)
    size_t redir_pos = input.find('>');
    if (redir_pos != std::string::npos) {
        bool append = (input.find(">>") != std::string::npos);
        std::string cmd_part = input.substr(0, redir_pos);
        std::string file_part = input.substr(redir_pos + (append ? 2 : 1));
        auto file_tokens = tokenize(file_part);
        if (file_tokens.empty()) return "Syntax error: missing file for redirection";

        std::string result = execute(cmd_part);
        auto active_fs = connected_host ? connected_host->get_fs() : fs;
        active_fs->touch(file_tokens[0], result); // Simplified (no append yet)
        return "";
    }

    // Very basic piping support (Act I level)
    size_t pipe_pos = input.find('|');
    if (pipe_pos != std::string::npos) {
        std::string left = input.substr(0, pipe_pos);
        std::string right = input.substr(pipe_pos + 1);

        std::string left_out = execute(left);
        if (right.find("grep") != std::string::npos) {
            auto r_tokens = tokenize(right);
            if (r_tokens.size() > 1) {
                std::string pattern = r_tokens[1];
                if (left_out.find(pattern) != std::string::npos) return left_out;
                return "";
            }
        }
        return left_out;
    }

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
    } else if (cmd == "exploit") {
        if (!connected_host) return "Not connected to any host";
        if (tokens.size() < 2) return "exploit: missing tool name";

        std::string tool = tokens[1];
        auto services = connected_host->get_services();
        if (services.empty()) return "No services found on target";

        // Try to exploit the first service found (simplified logic)
        if (tm->run_exploit(tool, services[0])) {
            // Grant admin access to the host's FS
            connected_host->get_fs()->cd("/"); // Ensure we start at root
            return "Exploit successful! Remote access granted.";
        }
        return "Exploit failed: Target patched or incompatible version.";
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
    } else if (cmd == "theme") {
        if (tokens.size() < 2) return "Usage: theme <green|amber|blue|white>";
        std::string t = tokens[1];
        if (t == "green" || t == "amber" || t == "blue" || t == "white") {
            return "__THEME_" + t + "__";
        }
        return "Unknown theme.";
    } else if (cmd == "shop") {
        return "--- Hardware & Software Shop ---\n"
               "[1] 14.4k Modem (Act II) - 500c\n"
               "[2] SkyNet v1.0.2 Exploit - 200c\n"
               "Use 'buy <id>' to purchase.";
    } else if (cmd == "buy") {
        if (tokens.size() < 2) return "buy: missing item id";
        if (tokens[1] == "2") {
            if (credits >= 200) {
                credits -= 200;
                tm->add_tool({"skynet_exploit_v102", "SkyNet-BBS", "1.0.2", 200});
                return "Purchased SkyNet v1.0.2 Exploit.";
            }
            return "Insufficient credits.";
        }
        return "Item not found.";
    } else if (cmd == "missions") {
        auto avail = mm->get_available_missions();
        std::string output = "--- Available Missions ---\n";
        for (const auto& m : avail) {
            output += "[" + m.id + "] " + m.title + " (" + std::to_string(m.credit_reward) + "c)\n";
        }
        return output;
    } else if (cmd == "cd") {
        if (tokens.size() > 1) {
            if (active_fs->cd(tokens[1])) return "";
            return "cd: " + tokens[1] + ": No such directory";
        }
        return "";
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
