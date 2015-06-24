#ifndef TRACKER_MESSAGES_H
#define TRACKER_MESSAGES_H
// This file includes all the messages that could be received by Tracker
#include "Message.h"

class Connection;


class TrackerMsg : public Message {
public:
    virtual void handle() = 0;
};

// send by uploader
class ServeTorrentRequest : public TrackerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};

// send by downloaer
class ListPeerRequest : public TrackerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};

// send by uploader
class HeartBeat : public TrackerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};


#endif 
