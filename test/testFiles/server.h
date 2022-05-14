#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "sendmessages.h"
#include "receivemessages.h"

#define PORT_PORT 1337

class Server
{

    

private: 
    int num, num2, clientLong;
    int clients[2];
    SendMessages* sendM_;
    ReceiveMessages* receiveM_;
    

public:
    Server();

    Server(SendMessages* sendM_);
    Server(ReceiveMessages* receiveM_);
  
    void sendMessage(const char* message, int client);
    void sendMessage(char *message, int client);
    void sendMessage(char *message, int client, int size);
    int getCardPetition();

    int readClient(int i);
    char* lastMessage;   
    void understandMessage(int i);
    char* buffer;
    char* name;
    bool newName = false;
    int cardPetition = 0;
    bool newCardPetition = true;
    int powerUpSelected = 0;
    int clientPowerUp = 0;
    int clientPetition = 0;
};

#endif // SERVER_H
