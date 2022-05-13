#include "server.h"

Server::Server(SendMessages* sendM) : 
    sendM_(sendM)
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

int Server::getCardPetition() {
    return 10;
}

