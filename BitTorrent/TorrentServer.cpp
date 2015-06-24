#include "TorrentServer.h"
#include <algorithm>
#include <iterator>
#include "Connection.h"
#include "Torrent.h"
#include "Log.h"

using namespace std;

std::shared_ptr<TorrentServer> TorrentServer::_instance{nullptr};

void TorrentServer::start(char* port){
    if (!_instance) {
        _instance.reset(new TorrentServer(port)); // cannot use make shared as constructor is private
    }
}

shared_ptr<TorrentServer> TorrentServer::instance(){
    if (!_instance) {
        logerr("Torrent Server has not been started");
    }
    return _instance;
}

void TorrentServer::add_torrent(shared_ptr<Torrent> torrent){
    if (torrents.count(torrent->hash())) {
        logerr("Already have the same torrent");
    }
    torrents[torrent->hash()] = torrent;
}

vector<string> TorrentServer::list_torrent(){
    vector<string> torrent_list;
    transform(torrents.begin(), torrents.end(),
              insert_iterator<vector<string>>(torrent_list, torrent_list.end()),
              mem_fn(&torrents_t::value_type::first));
    return torrent_list;
}

shared_ptr<Torrent> TorrentServer::get_torrent(const string t_hash){
    auto ite = torrents.find(t_hash);
    if (ite != torrents.end()) {
        return ite->second;
    }
    return nullptr;
}

shared_ptr<Connection> TorrentServer::get_connection(int sock_){
    return make_shared<TorrentServerWorker>(sock_);
}

TorrentServerWorker::TorrentServerWorker(int sock_) : Connection{sock_}{
}

void TorrentServerWorker::handle(){

}


