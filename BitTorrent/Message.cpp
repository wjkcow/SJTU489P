#include "Message.h"
#include "Connection.h"
#include "Log.h"
#include <iostream>

using namespace std;

const int reserve_size_c = sizeof(int32_t) + 1;

// <length> <message_ID> .<contents> ...
Message::Message() : data{reserve_size_c} {}

void Message::send_through(std::shared_ptr<Connection> connection){
    update_message_type();
    update_size();
    connection->send(data.data(), static_cast<int>(data.size()));
}


void Message::append_int32(int32_t i){
    char* value_ptr = reinterpret_cast<char*>(&i);
    data.insert(data.end(), value_ptr, value_ptr + sizeof(int32_t));
}

void Message::append_char(char c){
    data.push_back(c);
}

void Message::append_str(const char* c_str, int sz){
    data.insert(data.end(), c_str, c_str + sz);
}

void Message::append_str(const string& str){
    append_int32(static_cast<int32_t>(str.size()));
    append_str(str.c_str(), static_cast<int>(str.size()));
}

char* Message::get_buffer(int sz){
    int before_size = static_cast<int>(data.size());
    data.resize(before_size + sz);
    return &data[before_size];
}

void Message::update_size(){
    int sz = static_cast<int>(data.size()) - reserve_size_c;
    char* size_ptr = reinterpret_cast<char*>(&sz);
    copy(size_ptr, size_ptr + sizeof(int32_t), data.data());
}

void Message::update_message_type(){
    data[sizeof(int32_t)] = get_message_ID();
}
