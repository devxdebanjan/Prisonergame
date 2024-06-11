#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int guess(int a, int b) {         //generationg a guess within a 
    srand(time(0));
    int n = rand() % (b - a) + a;
    return n;
}

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
    cout << "Your Prisoner ID: " << sock << endl;
    int int1, int2, counter=0;
    send(sock, (char*)&counter, sizeof(counter), 0);
    recv(sock, (char*)&int1, sizeof(int), 0);
    recv(sock, (char*)&int2, sizeof(int), 0);
    cout << "Range for your guess: " << int1 << " --> " << int2 << endl;
    Sleep(2000);

    while (true)
        // Send the input to the server
    {
        int res, esc;
        int y = guess(int1, int2);
        cout << "CURRENT GUESS: " << y;                //guess sent by client/prisoner
        send(sock, (char*)&y, sizeof(y), 0);
        Sleep(1000);
        recv(sock, (char*)&res, sizeof(int), 0);
        //updating range
        if (res == -1) {
            cout << " Guess too low" << endl;
            int1 = y;
            cout << "Updated Range: " << int1 << " --> " << int2 << endl;
        }
        if (res == 1) {
            cout << " Guess too high" << endl;
            int2 = y;
            cout << "Updated Range: " << int1 << " --> " << int2 << endl;
        }
        if (res == 0) {
            cout << endl << " Congratulations!" << endl;
            cout << " Prison escaped" << endl;
            closesocket(sock);
            WSACleanup();
            break;
        }
    }

    return 0;
}
