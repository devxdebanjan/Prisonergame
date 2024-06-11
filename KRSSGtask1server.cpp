#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <cstdlib>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int l, r, x, c = 0, j = 0, n=4, flag=1;
int initial[25], final[25];

int guess(int a, int b) {        //finding a random number from a range 
    srand(time(0));
    int n = rand() % (b - a) + a;
    return n;
}

void clientHandler(SOCKET clientSocket) {       //Client Handler which handles each and every thread
    int count;
    recv(clientSocket, (char*)&count, sizeof(count), 0);
    if (count == 0) {
        send(clientSocket, (char*)(&l), sizeof(l), 0);
        send(clientSocket, (char*)(&r), sizeof(r), 0);
        int less = -1, more = 1, equal = 0;
        while (true) {
            int receivedFloat;
            int bytesReceived = recv(clientSocket, (char*)&receivedFloat, sizeof(receivedFloat), 0);
            if (bytesReceived == SOCKET_ERROR) {
                break;
            }
            else {
                if (flag) {
                    cout << "Received Guess: " << receivedFloat << " from Prisoner ID :" << clientSocket << endl;
                    if (receivedFloat < x) {
                        send(clientSocket, (char*)(&less), sizeof(less), 0);
                    }
                    if (receivedFloat > x) {
                        send(clientSocket, (char*)(&more), sizeof(more), 0);
                    }
                    if (receivedFloat == x) {
                        send(clientSocket, (char*)(&equal), sizeof(equal), 0);
                        int length = sizeof(final) / sizeof(final[0]);
                        int p = true;
                        for (int k = 0;k < length;k++) {
                            if (final[k] == clientSocket) {
                                p = false;
                            }
                        }
                        if (p) {
                            final[j] = clientSocket;
                            j++;
                        }

                    }
                    if (j == n) {
                        cout << endl << endl << "ORDER OF ESCAPE: " << endl;
                        for (int i = 0;i < n;i += 1)
                        {
                            cout << endl << endl << "Escape:" << (i + 1);
                            cout << " Prisoner ID: " << final[i] << endl;
                        }
                        flag = 0;
                        break;
                    }
                }
            }
        }
    }
    else {           //client number receiving 
        int num;
        recv(clientSocket, (char*)&num, sizeof(num), 0);
        n = num;
    }
    
}


int main() {                   
    srand(time(0));                          //generating the range for prisoners to guess from
    l = rand() % 45000;
    r = rand() % 45000 + 55000;
    x = guess(l, r);
    cout << "Correct Number which Prisoners have to Guess : " << x << endl;

    // Initialize Winsock
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        cerr << "Can't initialize Winsock! Quitting" << endl;
        return 1;
    }

    // Create a socket
    SOCKET servsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servsock == INVALID_SOCKET) {
        cerr << "Can't create a socket! Quitting" << endl;
        return 1;
    }

    // Bind the socket to an IP address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(9000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton ...

    bind(servsock, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(servsock, n+1);

    // Wait for a connection

    sockaddr_in client;
    int clientSize = sizeof(client);
    while (true) {

        SOCKET clientSocket = accept(servsock, (sockaddr*)&client, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Can't create client socket! Quitting" << endl;
            break;
        }
        if (c < n+1) {
            initial[c] = clientSocket;
            c++;
            cout << "Client connected!" << clientSocket << endl;
            // Create a thread for each client
            std::thread t(clientHandler, clientSocket);
            t.detach(); // Detach the thread so it runs independently
        }
        else {
            cout << "------- NO MORE SPACE FOR NEW PRISONERS -------" << endl;    //error message when more than desired number of clients are connected
        }
    }

    // Cleanup Winsock
    closesocket(servsock);
    WSACleanup();

    return 0;
}
