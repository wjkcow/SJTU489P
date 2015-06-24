#include "Torrent.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <iterator>
#include <cassert>
#include "hashlibpp.h"
#include "Log.h"

using namespace::std;
const int size_4m_c = 4 << 20;

Torrent::Torrent(const string& filename_, Address tracker_address): filename{filename_}, tracker(tracker_address){
    std::ifstream infile(filename_, ifstream::ate | std::ifstream::binary);
    if (!infile){
        cerr << "file cannot be opened" << endl;
        throw exception();
    }
    file_size = static_cast<int>(infile.tellg());
    infile.seekg(0);
    unique_ptr<char []> buffer{new char[size_4m_c]};
    int tmp_size{file_size};
    shared_ptr<hashwrapper> sha1 = make_shared<sha1wrapper>();
    while (tmp_size) {
        int read_size{tmp_size < size_4m_c ? tmp_size : size_4m_c};
        tmp_size -= read_size;
        infile.read(buffer.get(), read_size);
        if (!infile){
            assert(0);
        }
        filehash.push_back(sha1->getHashFromMemory(buffer.get(), read_size));
    }
    infile.close();
}

Torrent::Torrent(const std::string& content){
    stringstream ss(content);
    ss >> filename;
    ss >> file_size;
    int pieces;
    ss >> pieces;
    string hash;
    for (int i = 0; i < pieces; ++i) {
        ss >> hash;
        filehash.push_back(hash);
    }
    tracker = *Address::from_string(content.substr(ss.tellg()));
    if(!ss){
        logerr("Parsing error");
        throw exception();
    }
}

string Torrent::to_string(){
    stringstream ss;
    ss << filename << endl << file_size << endl << filehash.size()  << endl;
    for (auto ite =filehash.begin(); ite != filehash.end(); ++ ite) {
        ss << *ite << endl;
    }
    ss << tracker.to_string();
    return ss.str();
}



string Torrent::hash(){
    shared_ptr<hashwrapper> sha1 = make_shared<sha1wrapper>();
    return sha1->getHashFromString(to_string());
}

