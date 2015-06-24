
#ifndef TORRENT_SERVER_MESSAGES_H
#define TORRENT_SERVER_MESSAGES_H

// This file includes all the messages that could be received by TorrentServer

#include "Message.h"
#include "TorrentServer.h"
class Connection;

class TorrentServerMsg : public Message {
public:
    virtual void handle() = 0;
};

// Message send by uploader
class UploadTorrentRequest : public TorrentServerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};

// Message send by downloader
class DownloadTorrentRequest : public TorrentServerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};

// Message send by downloader
class ListTorrentRequest : public TorrentServerMsg{
public:
    void send_through(std::shared_ptr<Connection> connection);
};


#endif 
