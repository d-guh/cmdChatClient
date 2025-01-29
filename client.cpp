#include "client.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define DEBUG 1

int main(int argc, char* argv[]) {
    string input = "", username = "user", address = "127.0.0.1", port = "12345";
    if (argc != 4) {
        if (DEBUG) cout << "DEBUG: cmdline args not provided, prompting user..." << endl;

        cout << "Input your username (default: user): ";
        getline(cin, input);
        if (input != "") username = input;

        cout << "Input the address to connect to (default: 127.0.0.1): ";
        getline(cin, input);
        if (input != "") address = input;

        cout << "Input the port to connect on (default: 12345): ";
        getline(cin, input);
        if (input != "") port = input;
    } else {
        username = argv[1];
        address = argv[2];
        port = argv[3];
    }
    if (DEBUG) cout << "DEBUG: username: " << username << ", address: " << address << ", port: " << port << endl;
}