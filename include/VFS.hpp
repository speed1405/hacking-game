#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <chrono>

namespace vfs {

enum class NodeType { File, Directory };

struct Permissions {
    bool r = true;
    bool w = true;
    bool x = false;
};

struct VFSNode {
    std::string name;
    NodeType type;
    std::string content; // For files
    std::map<std::string, std::shared_ptr<VFSNode>> children; // For directories
    std::weak_ptr<VFSNode> parent;
    std::string owner = "user";
    std::string group = "user";
    Permissions perms;
    std::chrono::system_clock::time_point modified_at;

    VFSNode(std::string name, NodeType type)
        : name(name), type(type), modified_at(std::chrono::system_clock::now()) {}
};

class FileSystem {
public:
    FileSystem();

    std::shared_ptr<VFSNode> get_node(const std::string& path);
    bool mkdir(const std::string& path);
    bool touch(const std::string& path, const std::string& content = "");
    bool rm(const std::string& path);
    std::string pwd() const;
    bool cd(const std::string& path);
    std::vector<std::string> ls(const std::string& path = ".") ;

private:
    std::shared_ptr<VFSNode> root;
    std::shared_ptr<VFSNode> current_dir;
    std::vector<std::string> current_path;

    std::vector<std::string> split_path(const std::string& path) const;
};

} // namespace vfs
