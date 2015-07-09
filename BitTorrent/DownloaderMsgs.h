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

// send by uploader
class MsgHandShakeReply : public Message{
    
};

// send by uploader
class MsgBitField : public Message {
    
};

// send by uploader
class MsgReplyContent : public Message {
    
};

// send by uploader
class MsgHave : public Message {
    
};

#endif 
