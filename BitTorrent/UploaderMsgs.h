#ifndef UPLOADER_MESSAGES_H
#define UPLOADER_MESSAGES_H
// This file includes all the messages that could be received by Uploader
#include "Message.h"

class UploaderMsg : public Message{
public:
    virtual void handle();
};


class MsgHandshake : public UploaderMsg {
    
};

class MsgRequestContent : public UploaderMsg {
    
};



#endif 
