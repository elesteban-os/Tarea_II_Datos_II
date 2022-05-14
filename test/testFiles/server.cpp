#include "server.h"

Server::Server(SendMessages* sendM) : 
    sendM_(sendM)
{
    this->clients[0] = 1;
    this->clients[1] = 2;
}

Server::Server(ReceiveMessages* receiveM) : 
    receiveM_(receiveM)
{
    this->clients[0] = 1;
    this->clients[1] = 2;
}

/**
 * @brief Envía un mensaje a un cliente.
 * 
 * @param message mensaje
 * @param client cliente
 */
void Server::sendMessage(const char* message, int client) {
    num = sendM_->send(clients[client], message, strlen(message), 0);
}

/**
 * @brief Envía un mensaje a un cliente.
 * 
 * @param message mensaje, cliente.
 * @param client 
 */
void Server::sendMessage(char *message, int client) {
    num = sendM_->send(clients[client], message, strlen(message), 0);
}

/**
 * @brief Envía un mensaje a un cliente.
 * 
 * @param message mensaje.
 * @param client cliente.
 * @param size tamaño del mensaje.
 */
void Server::sendMessage(char *message, int client, int size) {
    num = sendM_->send(clients[client], message, size, 0);
}

/**
 * @brief Realiza una lectura de los jugadores.
 * 
 * @param i jugador.
 * @return int 
 */
int Server::readClient(int i) {
    int bufferLen = 1024;
    int num2;
    
    num2 = receiveM_->recv(clients[i], buffer, sizeof(buffer), 0);
    if (num2 != -1) {
        lastMessage = buffer;
        understandMessage(i);        
    } 

    return 1;

}     

/**
 * @brief Interpreta los mensajes recibidos para realizar su respectiva acción.
 * 
 * @param i jugador.
 */
void Server::understandMessage(int i) {
    const char *message1 = "name";
    const char *message2 = "card";
    const char *message3 = "pu1";
    const char *message4 = "pu2";
    const char *message5 = "pu3";
    
    if (strcmp(lastMessage, message1) == 0) {

        num2 = receiveM_->recv(clients[i], buffer, sizeof(buffer), 0);
        name = buffer;
        newName = true;
    }
    if (strcmp(lastMessage, message2) == 0) {
        num2 = receiveM_->recv(clients[i], buffer, sizeof(buffer), 0);
        if (num2 == 100) {
            cardPetition = 0;
        } else {
            cardPetition = num2;
        }
        newCardPetition = true;
        clientPetition = i;
    }
    if (strcmp(lastMessage, message3) == 0) {
        powerUpSelected = 1;
        clientPowerUp = i;
    }
    if (strcmp(lastMessage, message4) == 0) {
        powerUpSelected = 2;
        clientPowerUp = i;
    }
    if (strcmp(lastMessage, message5) == 0) {
        powerUpSelected = 3;
        clientPowerUp = i;
    }
}

int Server::getCardPetition() {
    return 10;
}

