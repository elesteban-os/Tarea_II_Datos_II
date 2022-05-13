#include "memory.h"


void Memory::randomCards() {
    if (noRandomTurns == 0) {
        int i = 0;
        int j = 0;
        int completeIndex = 0;
        int randomNum = 0;
        int readyNums[15];
        srand(time(0));
        for (int i = 0; i < 15; i++) {
            if (availableCards[i]) {
                readyNums[i] = 0;
            } else {
                completeIndex++;
                readyNums[i] = 2;
            }

        }
        while (completeIndex != 15) {
            randomNum = rand() % 15;
            while (readyNums[randomNum] == 2) {
                randomNum++;
                if (randomNum == 15) {
                    randomNum = 0;
                }
            }
            readyNums[randomNum]++;
            if (readyNums[randomNum] == 2) {
                completeIndex++;
            }
            bool ready = false;
            while (!ready) {
                if (j == 6) {
                    i++;
                    j = 0;
                }
                if (availableButtons[i][j]) {
                    cardsMatrix[i][j] = randomNum;
                    j++;
                    ready = true;
                } else {
                    cardsMatrix[i][j] = -1;
                    j++;
                }

            }

        }

    } else {
        noRandomTurns -= 1;
    }
}

/**
 * @brief Cambia el turno entre jugadores.
 */
void Memory::changeTurn() {
    if (game->getTurn() == 0) {
        game->setTurn(1);
    } else {
        game->setTurn(0);
    }
    if (game->getPlaying()) {
        server->sendMessage("turn", game->getTurn(), 4);
    }
}

/**
 * @brief Carga una nueva tarjeta en memoria.
 * @param id identificación de la tarjeta.
 */
void Memory::newCard(int id) {
    char* cardAddr;
    if (id == 0) {
        cardAddr = "images/0.jpg";
    } else if (id == 1) {
        cardAddr = "images/1.jpg";
    } else if (id == 2) {
        cardAddr = "images/2.jpg";
    } else if (id == 3) {
        cardAddr = "images/3.jpg";
    } else if (id == 4) {
        cardAddr = "images/4.jpg";
    } else if (id == 5) {
        cardAddr = "images/5.jpg";
    } else if (id == 6) {
        cardAddr = "images/6.jpg";
    } else if (id == 7) {
        cardAddr = "images/7.jpg";
    } else if (id == 8) {
        cardAddr = "images/8.jpg";
    } else if (id == 9) {
        cardAddr = "images/9.jpg";
    } else if (id == 10) {
        cardAddr = "images/10.jpg";
    } else if (id == 11) {
        cardAddr = "images/11.jpg";
    } else if (id == 12) {
        cardAddr = "images/12.jpg";
    } else if (id == 13) {
        cardAddr = "images/13.jpg";
    } else if (id == 14) {
        cardAddr = "images/14.jpg";
    }
    QImage image(cardAddr);

    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    inMemoryCards.add(data, size, id);
}

/**
 * @brief Obtiene una tarjeta que esté cargada en memoria si fuese el caso. En otro caso cargará la tarjeta en memoria.
 * 
 * @param x posición en x.
 * @param y posición en y.
 * @return char array de la imagen de la tarjeta. 
 */
char* Memory::getAnyCard(int x, int y) {
    int searchID = cardsMatrix[x][y];
    cardsSelected++;
    if (cardsSelected == 1) {
        cardSelected1 = searchID;
        firstButtonsSelected[0] = x;
        firstButtonsSelected[1] = y;
    } else {
        cardSelected2 = searchID;
    }
    char* data = inMemoryCards.getDataByID(searchID);
    if (data != NULL) {
        pageHit++;
        if (cardsSelected == 1) {
            pageHitCard = true;
        }
        return data;
    } else {
        inMemoryCards.deleteLastData();
        newCard(searchID);
        pageFault++;
        return inMemoryCards.getDataByID(searchID);
    }
}

/**
 * @brief Envía un indicador a un jugador.
 * 
 * @param player jugador.
 * @param indicator indicador.
 * @param button posición del botón.
 */
void Memory::sendEnemyOneIndicator(int player, int indicator, int button) {
    QImage image(adressIndicator[indicator]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    server->sendMessage("enemyCard", player, 9);
    server->sendMessage(data, player, size);
    server->sendMessage(" ", player, button);

    if (indicator == 1) {
        server->sendMessage(" ", player, 1);
    } else {
        server->sendMessage(" ", player, 2);
    }
}

/**
 * @brief Envía un indicador a un jugador.
 * 
 * @param player jugador.
 * @param indicator indicador.
 */
void Memory::sendPlayerOneIndicator(int player, int indicator) {
    QImage image(adressIndicator[indicator]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    server->sendMessage("imgq", player, 9);
    server->sendMessage(data, player, size);
}

/**
 * @brief Envía el resultado de la elección de las tarjetas.
 * 
 * @param result resultado.
 * @param player jugador.
 */
void Memory::sendResult(bool result, int player) {
    if (result) {
        sendPlayerOneIndicator(player, 1);
        if (player == 0) {
            sendEnemyOneIndicator(1, 1, buttonsSelected[0]);
            sendEnemyOneIndicator(1, 1, buttonsSelected[1]);
        } else {
            sendEnemyOneIndicator(0, 1, buttonsSelected[0]);
            sendEnemyOneIndicator(0, 1, buttonsSelected[1]);
        }
    } else {
        // Enviar resultado de fallar al jugador.
        sendPlayerOneIndicator(player, 0);
        if (player == 0) {
            sendEnemyOneIndicator(1, 0, buttonsSelected[0]);
            sendEnemyOneIndicator(1, 0, buttonsSelected[1]);
        } else {
            sendEnemyOneIndicator(0, 0, buttonsSelected[0]);
            sendEnemyOneIndicator(0, 0, buttonsSelected[1]);
        }
    }
    buttonsSelected[0] = -1;
    buttonsSelected[1] = -1;
    changeTurn();
}

void Memory::verifyInGameCards() {
    if (inGameCards == 0) {
        int sendToP1 = 0;
        int sendToP2 = 0;
        int scoreP1 = game->getScore(0);
        int scoreP2 = game->getScore(1);
        if (scoreP1 > scoreP2) {
            sendToP1 = 1;
            sendToP2 = 2;
        } else if (scoreP1 < scoreP2) {
            sendToP1 = 2;
            sendToP2 = 1;
        } else {
            sendToP1 = 3;
            sendToP2 = 3;
        }
        server->sendMessage("out", 0, 3);
        server->sendMessage(" ", 0, sendToP1);
        server->sendMessage("out", 1, 3);
        server->sendMessage(" ", 1, sendToP2);
    }
}

/**
 * @brief Recalcula las tarjetas que pueden estar en memoria.
 * 
 */
void Memory::recalculateInMemoryCards() {
    int newMaxCards = inGameCards / 3;
    if (newMaxCards > 0) {
        while (newMaxCards != maxMemoryCards) {
            inMemoryCards.deleteLastData();
            maxMemoryCards--;
        }
    }
}

/**
 * @brief Envía puntaje obtiendo a un jugador.
 * 
 * @param player jugador.
 */
void Memory::sendPoints(int player) {
    int points = 20;
    if (pageHitCard) {
        points *= 2;
        pageHitCard = false;
    }
    if (doublePointsPU) {
        points *= 2;
        doublePointsPU = false;
    }
    game->addScore(player, points);
    int score = game->getScore(player);
    sleep_for(std::chrono::milliseconds(10));
    if (player == 0) {
        server->sendMessage("playerPoints", 0, 12);
        server->sendMessage(" ", 0, score);
        server->sendMessage("enemyPoints", 1, 11);
        server->sendMessage(" ", 1, score);
    } else {
        server->sendMessage("playerPoints", 1, 12);
        server->sendMessage(" ", 1, score);
        server->sendMessage("enemyPoints", 0, 11);
        server->sendMessage(" ", 0, score);
    }
}

/**
 * @brief Guarda los botones que un jugador selecciona.
 * 
 * @param button posición del botón.
 */
void Memory::lastClientsButtons(int button) {
    if (buttonsSelected[0] == -1) {
        buttonsSelected[0] = button;
    } else {
        buttonsSelected[1] = button;
    }
}

/**
 * @brief envía una carta que un jugador está esperando.
 * 
 * @param image imágen de la tarjeta.
 * @param clientPetition cliente que necesita la tarjeta.
 */
void Memory::sendPlayersCard(char* image, int clientPetition) {
    server->sendMessage("card", clientPetition, 4);
    server->sendMessage(image, clientPetition, 47000);

    int cardPetition = 0;
    if (server->getCardPetition() == 0) {
        cardPetition = 100;
    } else {
        cardPetition = server->getCardPetition();
    }
    lastClientsButtons(cardPetition);

    if (clientPetition == 0) {
        server->sendMessage("enemyCard", 1, 9);
        server->sendMessage(image, 1, 47000);
        server->sendMessage(" ", 1, cardPetition);
        server->sendMessage(" ", 1, 2);
    } else {
        server->sendMessage("enemyCard", 0, 9);
        server->sendMessage(image, 0, 47000);
        server->sendMessage(" ", 0, cardPetition);
        server->sendMessage(" ", 0, 2);
    }
}

// Se debe enviar a todos los clientes.
/**
 * @brief Envía indicadores de tarjetas a los jugadores.
 * 
 */
void Memory::sendQuestionImages() {
    QImage image(adressIndicator[0]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    for (int i = 0; i < 2; i++) {
        server->sendMessage("imgq", i, 4);
        server->sendMessage(data, i, size);
    }
    game->setTurn(0);
}

void Memory::sendPlayersName() {
    server->sendMessage("enemyName", 0, 9);
    server->sendMessage(game->getPlayer2name(), 0, strlen(game->getPlayer2name()));
    server->sendMessage("enemyName", 1, 9);
    server->sendMessage(game->getPlayer1name(), 1, strlen(game->getPlayer1name()));
}
