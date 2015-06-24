#ifndef TRACKER_MESSAGES_H
#define TRACKER_MESSAGES_H
// This file includes all the messages that could be received by Tracker
#include <memory>
#include <string>
#include "Message.h"

const char serve_torrent_ID_c = 1;
const char list_peer_ID_c = 2;
const char heartbeat_ID_c = 3;

class Connection;
class TrackerWorker;

class TrackerMsg : public Message {
public:
    virtual void handle(std::shared_ptr<TrackerWorker>) = 0;
};

// send by uploader
class ServeTorrentRequest : public TrackerMsg{
public:
    ServeTorrentRequest(const std::string& torrent_id_);
    void handle(std::shared_ptr<TrackerWorker>) override;
    
protected:
    std::string torrent_id;
    char get_message_ID() override {return serve_torrent_ID_c;}
    
};

// send by downloaer
class ListPeerRequest : public TrackerMsg{
public:
    void handle(std::shared_ptr<TrackerWorker>) override;
protected:
    char get_message_ID() override {return list_peer_ID_c;}
    

};

// send by uploader
class HeartBeat : public TrackerMsg{
public:
    void handle(std::shared_ptr<TrackerWorker>) override;
protected:
    char get_message_ID() override {return heartbeat_ID_c;}
};


#endif 
