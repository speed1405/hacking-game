#include "VFS.hpp"
#include <sstream>
#include <algorithm>

namespace vfs {

FileSystem::FileSystem() {
    root = std::make_shared<VFSNode>("/", NodeType::Directory);
    current_dir = root;
}

std::vector<std::string> FileSystem::split_path(const std::string& path) const {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(path);
    while (std::getline(tokenStream, token, '/')) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

std::shared_ptr<VFSNode> FileSystem::get_node(const std::string& path) {
    if (path == "/") return root;
    if (path == "." || path.empty()) return current_dir;

    auto tokens = split_path(path);
    std::shared_ptr<VFSNode> current = (path[0] == '/') ? root : current_dir;

    for (const auto& token : tokens) {
        if (token == "..") {
            // This would require parent pointers in VFSNode or tracking path in FS
            // For now, let's just stay at current if we can't go up
            continue;
        }
        if (current->children.count(token)) {
            current = current->children[token];
        } else {
            return nullptr;
        }
    }
    return current;
}

bool FileSystem::touch(const std::string& path, const std::string& content) {
    auto tokens = split_path(path);
    if (tokens.empty()) return false;

    std::string file_name = tokens.back();
    tokens.pop_back();

    std::shared_ptr<VFSNode> parent = current_dir;
    if (path[0] == '/') parent = root;

    for (const auto& token : tokens) {
        if (parent->children.count(token) && parent->children[token]->type == NodeType::Directory) {
            parent = parent->children[token];
        } else {
            return false;
        }
    }

    auto new_file = std::make_shared<VFSNode>(file_name, NodeType::File);
    new_file->content = content;
    parent->children[file_name] = new_file;
    return true;
}

bool FileSystem::mkdir(const std::string& path) {
    auto tokens = split_path(path);
    if (tokens.empty()) return false;

    std::string dir_name = tokens.back();
    tokens.pop_back();

    std::shared_ptr<VFSNode> parent = current_dir;
    if (path[0] == '/') parent = root;

    for (const auto& token : tokens) {
        if (parent->children.count(token) && parent->children[token]->type == NodeType::Directory) {
            parent = parent->children[token];
        } else {
            return false;
        }
    }

    if (parent->children.count(dir_name)) return false;

    auto new_dir = std::make_shared<VFSNode>(dir_name, NodeType::Directory);
    parent->children[dir_name] = new_dir;
    return true;
}

bool FileSystem::cd(const std::string& path) {
    auto node = get_node(path);
    if (node && node->type == NodeType::Directory) {
        current_dir = node;
        return true;
    }
    return false;
}

std::vector<std::string> FileSystem::ls(const std::string& path) {
    auto node = get_node(path);
    std::vector<std::string> results;
    if (node && node->type == NodeType::Directory) {
        for (const auto& [name, child] : node->children) {
            results.push_back(name);
        }
    }
    return results;
}

} // namespace vfs
