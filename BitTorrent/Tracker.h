#ifndef TRACKER_H
#define TRACKER_H

#include "Server.h"
#include "Peer.h"
#include <vector>
#include <mutex>
#include <memory>
#include <map>

class Connection;

class TrackerServer : public Server{
public:
    
protected:
    std::shared_ptr<Connection> get_connection(int sock_);
private:
    std::mutex peer_mtx;
    std::map<std::string, Peer> torrent_peer;
    std::vector<Peer> peers;
    std::vector<Peer> time_out_peers;
    
};

class TrackerServerWorker : public Connection{
public:
    TrackerServerWorker(int sock_);
private:
    void handle();
};


#endif