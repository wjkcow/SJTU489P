#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <memory>
#include <vector>
#include "Connection.h"
class Server {
public:
    Server(const char* port);
    virtual ~Server();
    void drop_connection(std::shared_ptr<Connection> connection);
protected:
    virtual std::shared_ptr<Connection> get_connection(int sock_) = 0;
private:
    int listen_sock;
    void accept_connection();

    std::vector<std::shared_ptr<Connection>> connections;
    std::thread _thread;
};

#endif
