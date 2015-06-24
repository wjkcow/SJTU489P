#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include <exception>
class Message;

class Connection :
public std::enable_shared_from_this<Connection>{
public:
    virtual ~Connection();
    Connection(int sock_) : sock{sock_} {}
  //  std::shared_ptr<Message> recv_message();
    
    int  get_int32();
    char get_char();
    void get_str(char* buffer, int sz);
    
    
    void send(char* buffer, int sz);
private:
    int sock;
    bool force_receive(void* buffer, int sz);

    class UnableToReadFromConnection : public std::exception{
        const char* what() const noexcept
        {return "Unable to read from this connection \n";}
    };
    
    class UnableToSendToConnection : public std::exception{
        const char* what() const noexcept
        {return "Unable to send to this connection \n";}
    };
};


#endif
