#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string.h>
#include <iostream>
#include <QDebug>

#define PORT_PORT 1337

using std::this_thread::sleep_for;

class Server
{
private: 
    WSADATA WsaData;
    int num, num2, clientLong;
    int bufferLen = 1024;
    bool readyQuestionImage = false;
    char buffer[1024];
    char name[1024];
    bool newName = false;
    int cardPetition = 0;
    bool newCardPetition = false;
    int clientPetition = 0;
    struct sockaddr_in server1;
    struct sockaddr_in client1;
    int serverSocket = 0;
    int clients[2];
    int i = 0;
    char lastMessage[1024];   
    std::thread t; 
    std::thread tacpt;
    int powerUpSelected = 0;
    int clientPowerUp = -1;

    void writeLastMessage(char message[], int len);
    int readClient(int i);
    int wsaCreate();
    int createServerSocket();
    int addressCreate();
    int bindServerSocket();
    int listenServerSocket();
    int acceptSocket();
    void understandMessage(int i);


public:
    Server();
    char* getLastMessage();
    int startServer();
    void sendMessage(const char* message, int client);
    void sendMessage(char *message, int client);
    void sendMessage(char *message, int client, int size);
    void setZeroesLastMessage();
    bool getReadyQuestionImage();

    bool getNewNameBool();
    void setNewNameBool(bool name);

    char* getName();
    void clearName();

    int getCardPetition();
    bool getNewCardPetition();
    void setNewCardPetition(bool value);
    int getClientPetition();

    int getPowerUpSelected();
    void setPowerUpSelected(int value);
    int getClientPowerUp();
    void setClientPowerUpSelected(int value);


};

#endif // SERVER_H
