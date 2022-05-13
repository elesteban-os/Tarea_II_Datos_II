#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "sendmessages.h"

#define PORT_PORT 1337


class Server
{

    

private: 
    int num, num2, clientLong;
    int clients[2];
    SendMessages* sendM_;
    

public:
    Server();

    Server(SendMessages* sendM_);
  
    void sendMessage(const char* message, int client);
    void sendMessage(char *message, int client);
    void sendMessage(char *message, int client, int size);
    int getCardPetition();
};

#endif // SERVER_H
