#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "Connection.h"
class ClientConnection : public Connection{
public:
    ClientConnection(char* host, char* port);
private:
    int setup_connection(char* host, char* port);
};

#endif 
