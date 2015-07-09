#include "TrackerMsgs.h"

#include "Tracker.h"

using namespace std;

ServeTorrentRequest::ServeTorrentRequest(const std::string& torrent_id_) :
torrent_id{torrent_id_}{
    append_str(torrent_id);
}

void ServeTorrentRequest::handle(shared_ptr<TrackerWorker> worker){
    worker->handle(shared_from_this());
}

void ListPeerRequest::handle(shared_ptr<TrackerWorker> worker){
    worker->handle(shared_from_this());
}

void HeartBeat::handle(shared_ptr<TrackerWorker> worker){
    worker->handle(shared_from_this());
}
