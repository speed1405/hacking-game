#include "Network.hpp"

namespace network {

Host::Host(std::string ip, std::string hostname) : ip(ip), hostname(hostname) {
    fs = std::make_shared<vfs::FileSystem>();
}

void Host::add_service(Service svc) {
    services.push_back(svc);
}

void Network::add_host(std::shared_ptr<Host> host) {
    hosts[host->get_ip()] = host;
}

std::shared_ptr<Host> Network::find_host(const std::string& address) {
    if (hosts.count(address)) return hosts[address];
    return nullptr;
}

} // namespace network
