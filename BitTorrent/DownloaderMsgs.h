#ifndef DOWNLOADER_MESSAGES_H
#define DOWNLOADER_MESSAGES_H

#include "Message.h"

// Message send by torrent server
class ListTorrentResponse : public Message {
public:
    void send_through(std::shared_ptr<Connection> connection);
};


// send by tracker, recv by downloader
class ListPeerResponse : public Message{
public:
    void send_through(std::shared_ptr<Connection> connection);
};

#endif 
