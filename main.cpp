#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "VFS.hpp"
#include "Shell.hpp"

using namespace ftxui;

int main() {
    auto fs = std::make_shared<vfs::FileSystem>();
    auto net = std::make_shared<network::Network>();
    auto pc = std::make_shared<hardware::PC>();
    auto mm = std::make_shared<missions::MissionManager>();

    // Seed some hosts
    auto local = std::make_shared<network::Host>("127.0.0.1", "localhost");
    local->get_fs()->mkdir("home");
    local->get_fs()->mkdir("home/user");
    local->get_fs()->touch("home/user/read_me.txt", "The world is bigger than your bedroom. -Vapor");
    net->add_host(local);

    auto bbs = std::make_shared<network::Host>("555-0123", "skynet-bbs");
    bbs->add_service({"SkyNet-BBS", "1.0.2", 23});
    bbs->get_fs()->mkdir("private");
    bbs->get_fs()->touch("private/salary_list.txt", "Confidential Salary Data...");
    net->add_host(bbs);

    // Seed missions
    mm->add_mission({"M-PRO", "Prologue: The Acoustic Coupler", "Explore your local machine and find Vapor's message.", "127.0.0.1", 0, 0});
    mm->add_mission({"M-01", "Act I: The First Breach", "Dial into SkyNet BBS (555-0123) and locate the salary list.", "555-0123", 100, 10});

    auto shell = std::make_unique<shell::Shell>(fs, net, pc, mm);

    std::vector<std::string> history;
    std::string input_content;

    auto screen = ScreenInteractive::TerminalOutput();

    Component input = Input(&input_content, "Type a command...");

    auto command_handler = CatchEvent(input, [&](Event event) {
        if (event == Event::Return) {
            history.push_back(shell->get_prompt() + input_content);
            std::string result = shell->execute(input_content);
            if (result == "__CLEAR__") {
                history.clear();
            } else if (!result.empty()) {
                history.push_back(result);
            }
            input_content = "";
            return true;
        }
        return false;
    });

    auto renderer = Renderer(command_handler, [&] {
        Elements history_elements;
        for (const auto& line : history) {
            history_elements.push_back(text(line));
        }

        return vbox({
            vbox(std::move(history_elements)),
            hbox(text(shell->get_prompt()), input->Render())
        }) | border;
    });

    screen.Loop(renderer);

    return 0;
}
