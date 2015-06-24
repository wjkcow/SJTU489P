#ifndef TORRENT_H
#define TORRENT_H

#include <memory>
#include <string>
#include <vector>
#include "Address.h"

class Connection;

class Torrent{
public:

    Torrent(const std::string& file, Address tracker_address);
    Torrent(const std::string& content);
        
    std::string to_string();
    
    Address get_tracker();
    
    std::string get_filename(){
        return filename;
    }
    
    int get_file_size(){
        return file_size;
    }
    
    int get_piece_number(){
        return static_cast<int>(filehash.size());
    }
    
    std::string get_hash(int piece){
        return filehash[piece];
    }
    
    std::string hash();
    
private:
    Address tracker;
    int file_size;
    std::string filename;
    std::vector<std::string> filehash;
};

#endif 
