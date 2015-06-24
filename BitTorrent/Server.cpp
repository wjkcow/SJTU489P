#include "Server.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdint>
#include <iostream>
#include "Log.h"
#include <exception>


Server::Server(const char* port){
    int rc;
    
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    addrinfo *ai;
    getaddrinfo(nullptr, port, &hints, &ai);
    
    if (rc) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        throw std::exception();
    }
    
    listen_sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (listen_sock < 0) {
        logerr("creating socket");
        throw std::exception();
    }
    
    int yes = 1;
    rc = setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if (rc) {
        logerr("setsockopt failed");
        throw std::exception();
    }
    
    rc = bind(listen_sock, ai->ai_addr, ai->ai_addrlen);
    if (rc) {
        logerr("bind failed");
        throw std::exception();
    }
    
    freeaddrinfo(ai);
    
    rc = listen(listen_sock, 10);
    if (rc) {
        logerr("listen failed");
        throw std::exception();
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    
    rc = getsockname(listen_sock, (struct sockaddr *)&addr, &len);
    if (rc) {
        logerr("getsockname failed");
        throw std::exception();
    }
    std::cout << "Server accepting connection " << ntohs(addr.sin_port) << std::endl;
    _thread = std::thread(&Server::accept_connection, this);
   // add_task(std::bind(&ServerConnection::accept_connection, this));
}

Server::~Server(){
    log("Server connection is going to be closed");
    close(listen_sock);
}

void Server::drop_connection(std::shared_ptr<Connection> connection){
    connections.erase(std::find(connections.begin(), connections.end(), connection));
}

void Server::accept_connection(){
    while (true) {
        log("Server is accepting connection");
        int socket = accept(listen_sock, nullptr, 0);
        log("New connection accepted");
        connections.push_back(get_connection(socket));
    }
}
