#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "VFS.hpp"

namespace network {

struct Service {
    std::string name;
    std::string version;
    int port;
};

class Host {
public:
    Host(std::string ip, std::string hostname);
    void add_service(Service svc);
    std::string get_ip() const { return ip; }
    std::string get_hostname() const { return hostname; }
    const std::vector<Service>& get_services() const { return services; }
    std::shared_ptr<vfs::FileSystem> get_fs() { return fs; }

private:
    std::string ip;
    std::string hostname;
    std::vector<Service> services;
    std::shared_ptr<vfs::FileSystem> fs;
};

class Network {
public:
    void add_host(std::shared_ptr<Host> host);
    std::shared_ptr<Host> find_host(const std::string& address); // IP or Phone

private:
    std::map<std::string, std::shared_ptr<Host>> hosts;
};

} // namespace network
