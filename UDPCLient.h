#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "string"
#include "cstring"
#include "iostream"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

using namespace std;

class UDPClient {
public:
    UDPClient(const char* ip, int port);
    ~UDPClient();
    void sendRequestLogin(string username,string password);
    bool receiveResponse();
private:
    int clientSocket;
    struct sockaddr_in serverAddr;
};

#endif // UDPCLIENT_H
