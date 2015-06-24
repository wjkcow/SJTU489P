#include "TorrentServerMsgs.h"

#include <string>
#include "TorrentServer.h"
#include "Torrent.h"
#include "Connection.h"

using namespace std;

UploadTorrentRequest::UploadTorrentRequest(std::shared_ptr<Torrent> torrent_ptr_) : torrent_ptr{torrent_ptr_} {
    append_str(torrent_ptr->to_string());
}

UploadTorrentRequest::UploadTorrentRequest(std::shared_ptr<Connection> connection) : torrent_ptr{make_shared<Torrent>(connection->get_str())}{
}

void UploadTorrentRequest::handle(std::shared_ptr<TorrentServerWorker> worker){
    worker->handle(shared_from_this());
}

DownloadTorrentRequest::DownloadTorrentRequest(std::shared_ptr<Connection> connection){
    torrent_id = connection->get_str();
    append_str(torrent_id);
}

void DownloadTorrentRequest::handle(std::shared_ptr<TorrentServerWorker> worker){
    worker->handle(shared_from_this());
}

