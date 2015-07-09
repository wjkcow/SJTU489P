#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <memory>
#include <exception>
#include <cstdint>

const char default_message_id_c = 0;
class Connection;

class Message {
public:
    Message();
    virtual ~Message(){}
    
    virtual void send_through(std::shared_ptr<Connection> connection);

    Message(const Message&) = delete;
    Message(Message&&) = delete;
    Message& operator=(const Message&) = delete;
    Message& operator=(Message&&) = delete;
    
protected:
    virtual char get_message_ID() {return default_message_id_c;}
    
    void append_int32(int32_t i);
    void append_char(char c);
    void append_str(const char* c_str, int sz);
    void append_str(const std::string& str);

    char* get_buffer(int sz);
private:
    void update_size();
    void update_message_type();
    
    std::vector<char> data;
};

#endif
