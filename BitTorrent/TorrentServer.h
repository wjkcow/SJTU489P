#ifndef TORRENT_SERVER_H
#define TORRENT_SERVER_H
#include "Server.h"
#include <memory>
#include <map>
#include <string>

class Connection;
class Torrent;

class UploadTorrentRequest;
class DownloadTorrentRequest;
class ListTorrentRequest;

class TorrentServer : public Server{
public:
    using torrents_t = std::map<std::string, std::shared_ptr<Torrent>>;
    static void start(char* port);
    static std::shared_ptr<TorrentServer> instance();
    
    void add_torrent(std::shared_ptr<Torrent> torrent);
    std::vector<std::string> list_torrent();
    std::shared_ptr<Torrent> get_torrent(const std::string t_hash);
    
protected:
    std::shared_ptr<Connection> get_connection(int sock_);
private:
    TorrentServer(char* port): Server(port){
    }
    

    torrents_t torrents;
    static std::shared_ptr<TorrentServer> _instance;
};

class TorrentServerWorker : public Connection,
public std::enable_shared_from_this<TorrentServerWorker>{
public:
    TorrentServerWorker(int sock_);
    void handle(std::shared_ptr<UploadTorrentRequest> request){}
    void handle(std::shared_ptr<DownloadTorrentRequest> request){}
    void handle(std::shared_ptr<ListTorrentRequest> request){}
    
private:
    void handle();
};
#endif
