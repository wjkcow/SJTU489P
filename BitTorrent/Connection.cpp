#include "Connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdint>

Connection::~Connection(){
    close(sock);
}

int Connection::get_int32(){
    int32_t i;
//    ssize_t read_len = recv(sock, &i, sizeof(int32_t), 0);
//    if (read_len != sizeof(int32_t)) {
//        throw UnableToReadFromConnection();
//    }
    if (!force_receive(&i, sizeof(int32_t))) {
        throw UnableToReadFromConnection();
    }
    return i;
}

char Connection::get_char(){
    char c;
    ssize_t read_len = recv(sock, &c, sizeof(char), 0);
    if (read_len != sizeof(char)) {
        throw UnableToReadFromConnection();
    }
    return c;
}

void Connection::get_str(char* buffer, int sz){
//    ssize_t read_len = recv(sock, buffer, sz, 0);
//    if (read_len != sz) {
//        throw UnableToReadFromConnection();
//    }
    
    if (!force_receive(buffer, sz)) {
        throw UnableToReadFromConnection();
    }
}

void Connection::send(char* buffer, int size){
    ::send(sock, buffer, size, 0);
}

bool Connection::force_receive(void* buffer, int sz){
    ssize_t read_len{0};
    while (read_len < sz) {
        ssize_t new_read_len = recv(sock, (char *)buffer + read_len, sz - read_len, 0);
        if (new_read_len == 0) {
            return false;
        }
        read_len += new_read_len;
    }
    return true;
}

