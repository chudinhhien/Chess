#include "UDPCLient.h"

using namespace std;

UDPClient::UDPClient(const char* ip, int port) {
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(clientSocket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    if(inet_pton(AF_INET,ip,&serverAddr.sin_addr) < 0){
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }
}

UDPClient::~UDPClient(){
    close(clientSocket);
}

void UDPClient::sendRequestLogin(string username,string password){
    string message = username + " " + password;
    ssize_t bytesSent = sendto(clientSocket, message.c_str(),message.size(),0,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    cout << message.c_str() << endl;
    if (bytesSent < 0) {
        cout << "Send failed" << endl;
    }
}

bool UDPClient::receiveResponse() {
    // Thực hiện nhận phản hồi từ server (cần được cài đặt)
    // Đây chỉ là một ví dụ cơ bản
    char buffer[1024];
    socklen_t addrLen = sizeof(serverAddr);
    ssize_t bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0,(struct sockaddr*)&serverAddr, &addrLen);
    if (bytesReceived < 0) {
        std::cerr << "Receive failed" << std::endl;
        return "";
    }
    buffer[bytesReceived] = '\0'; // Đảm bảo kết thúc chuỗi
    if(string(buffer) == "false") {
        return false;
    }
    return true;
}
