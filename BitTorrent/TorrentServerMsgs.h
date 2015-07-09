
#ifndef TORRENT_SERVER_MESSAGES_H
#define TORRENT_SERVER_MESSAGES_H

// This file includes all the messages that could be received by TorrentServer

#include <memory>
#include "Message.h"
#include "TorrentServer.h"
#include "Connection.h"

class Connection;
class Torrent;

const int upload_torrent_ID_c = 1;
const int download_torrent_ID_c = 2;
const int list_torrent_ID_c = 3;

class TorrentServerMsg : public Message {
public:
    virtual void handle(std::shared_ptr<TorrentServerWorker>) = 0;
};

// Message send by uploader
class UploadTorrentRequest : public TorrentServerMsg,
public std::enable_shared_from_this<UploadTorrentRequest>
{
public:
    UploadTorrentRequest(std::shared_ptr<Torrent> torrent_ptr);
    UploadTorrentRequest(std::shared_ptr<Connection> connection);
    
    void handle(std::shared_ptr<TorrentServerWorker>) override;
    
    std::shared_ptr<Torrent> get_torrent(){
        return torrent_ptr;
    }
    
protected:
    char get_message_ID() override {return upload_torrent_ID_c;}
    
private:
    std::shared_ptr<Torrent> torrent_ptr;
};

// Message send by downloader
class DownloadTorrentRequest : public TorrentServerMsg,
public std::enable_shared_from_this<DownloadTorrentRequest>{
public:
    DownloadTorrentRequest(const std::string& torrent_id_);
    DownloadTorrentRequest(std::shared_ptr<Connection> connection);
    
    void handle(std::shared_ptr<TorrentServerWorker>) override;
    
    std::string get_torrent_id(){
        return torrent_id;
    }
protected:
    char get_message_ID() override {return download_torrent_ID_c;}

private:
    std::string torrent_id;

};

// Message send by downloader
class ListTorrentRequest : public TorrentServerMsg,
public std::enable_shared_from_this<ListTorrentRequest>{
public:
    void handle(std::shared_ptr<TorrentServerWorker>) override;
protected:
    char get_message_ID() override {return list_torrent_ID_c;}
};


#endif 
