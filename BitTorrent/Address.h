#ifndef ADDRESS_H
#define ADDRESS_H

#include <Memory>
#include <string>

class Address{
public:
    
    std::string to_string(){
        return std::string();
    }
    
    static std::shared_ptr<Address> from_string(const std::string& str){
        return std::make_shared<Address>();
    }
};
#endif
