#ifndef TRACKER_H
#define TRACKER_H

#include "Server.h"
#include "Peer.h"
#include <vector>
#include <mutex>
#include <memory>
#include <map>

class Connection;
class ServeTorrentRequest;
class ListPeerRequest;
class HeartBeat;

class Tracker : public Server{
public:
    
protected:
    std::shared_ptr<Connection> get_connection(int sock_);
private:
    std::mutex peer_mtx;
    std::map<std::string, Peer> torrent_peer;
    std::vector<Peer> peers;
    std::vector<Peer> time_out_peers;
    
};

class TrackerWorker : public Connection{
public:
    TrackerWorker(int sock_);
    
    void handle(std::shared_ptr<ServeTorrentRequest>){}
    void handle(std::shared_ptr<ListPeerRequest>){}
    void handle(std::shared_ptr<HeartBeat>){}

private:
    void handle();
};


#endif
