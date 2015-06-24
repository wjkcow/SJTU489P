#include "ClientConnection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <exception>
#include "Log.h"

ClientConnection::ClientConnection(char* host, char* port) :
Connection(setup_connection(host, port)){

}

int ClientConnection::setup_connection(char* host, char* port){
    int rc;
    
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    addrinfo *ai;
    rc = getaddrinfo(host, port, &hints, &ai);
    if (rc) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        throw std::exception();
    }
    
    int sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (sock < 0) {
        logerr("creating socket");
        throw std::exception();
    }
    
    rc = connect(sock, ai->ai_addr, ai->ai_addrlen);
    if (rc) {
        logerr("failed to connect");
        throw std::exception();
    }
    
    freeaddrinfo(ai);
    
    return sock;
}
