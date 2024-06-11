#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main() {
    // Initialize Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0) {
        cerr << "Can't initialize Winsock! Quitting" << endl;
        return 1;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Can't create socket! Quitting" << endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

    int conn = connect(sock, (sockaddr*)&srv, sizeof(srv));
    if (conn == SOCKET_ERROR) {
        cerr << "Can't connect to server! Quitting" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    int counter = 1;
    send(sock, (char*)&counter, sizeof(counter), 0);
    //asking user for input
    cout << "Enter the number of prisoners to connect: " << endl;
    int n;
    cin >> n;
    send(sock, (char*)&n, sizeof(n), 0);
    return 0;
}
