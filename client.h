// client.h
// Headerfile for cmdChatClient.

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEBUG 1

using namespace std;

class Client {
public:
    Client(const string& username, const string& address, int port) : client_username(username), server_address(address), server_port(port) {}
    void start();

private:
    string client_username;
    string server_address;
    int server_port;
    int sockfd;
    thread recieve_thread;
    mutex cout_mutex;

    void connect_to_server();
    void send_messages();
    void recieve_messages();
};

#endif
