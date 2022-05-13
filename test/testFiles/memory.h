#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <time.h>
#include <string.h>
#include "game.h"
#include "server.h"
#include "qimage.h"
#include "linkedcard.h"

#include "mockSendMessages.h"

using std::this_thread::sleep_for;

class Memory
{
private:
    // Random cards
    int noRandomTurns = 0;

    MockSendMessages mock;

    
    
public:
    // Random cards
    int cardsMatrix[5][6];
    bool availableCards[15] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool availableButtons[5][6] = {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}};
    const char *adressCards[15] = { "images/0.jpg", "images/1.jpg", "images/2.jpg", "images/3.jpg", "images/4.jpg",
                                    "images/5.jpg", "images/6.jpg", "images/7.jpg", "images/8.jpg", "images/9.jpg",
                                    "images/10.jpg", "images/11.jpg", "images/12.jpg", "images/13.jpg", "images/14.jpg" };
    void randomCards();

    // Cambiar turno
    void changeTurn();

    // Game
    Game *game = new Game;

    // Server
    Server *server;

    // Nueva tarjeta
    void newCard(int id);
    linkedCard inMemoryCards;

    // Obtener tarjeta
    char* getAnyCard(int x, int y);
    int cardsSelected = 0;
    int cardSelected1 = -1;
    int cardSelected2 = -1;
    int pageHit = 0;
    int pageFault = 0;
    int firstButtonsSelected[2] = {-1, -1};
    bool pageHitCard = false;

    // Enviar indicador
    void sendEnemyOneIndicator(int player, int indicator, int button);
    char *adressIndicator[2] = {"images/question.jpg", "images/correct.jpg"};
    void sendPlayerOneIndicator(int player, int indicator);

    // Enviar resultado
    void sendResult(bool result, int player);
    int buttonsSelected[2] = {-1, -1};

    // Verificar las cartas en juego
    void verifyInGameCards();
    int inGameCards = 15;

    // Cartas en memoria 
    void recalculateInMemoryCards();
    int maxMemoryCards = 5;

    // Enviar puntajes
    void sendPoints(int player);
    bool doublePointsPU = false;

    // Guardar botones seleccionados por el cliente
    void lastClientsButtons(int button);

    // Enviar tarjeta seleccionada clientes.
    void sendPlayersCard(char* image, int clientPetition);

    // Enviar las imagenes question
    void sendQuestionImages();

    // Enviar nombres
    void sendPlayersName();
};


#endif // MEMORY_H
