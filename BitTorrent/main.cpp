#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    string str = "123 1234";
    stringstream ss{str};
    int i ;
    ss >> i;
    cout << str.substr(ss.tellg()) << endl;
    return 0;
}
