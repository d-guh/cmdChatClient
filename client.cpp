// client.cpp
// cmdChatClient to handle send and recv.

#include "client.h"

void Client::start() {
    if (DEBUG) cout << "DEBUG: Starting client..." << endl;
    connect_to_server();
    send(sockfd, client_username.c_str(), client_username.size(), 0); // Send username to server
    recieve_thread = thread(&Client::recieve_messages, this);
    send_messages();
}

void Client::connect_to_server() {
    if (DEBUG) cout << "DEBUG: Connecting to server at " << server_address << ":" << server_port << endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_address.c_str(), &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (DEBUG) cout << "DEBUG: Connected to server." << endl;
}

void Client::send_messages() {
    string message;
    while (true) {
        getline(cin, message);
        send(sockfd, message.c_str(), message.size(), 0);
        if (DEBUG) cout << "DEBUG: Sent message: " << message << endl;
    }
}

void Client::recieve_messages() {
    char buffer[1024];
    while (true) {
        int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            lock_guard<mutex> lock(cout_mutex);
            cout << buffer << endl;
            if (DEBUG) cout << "DEBUG: Received message: " << buffer << endl;
        }
    }
}

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

    Client client(username, address, stoi(port));

    client.start();

    return 0;
}
