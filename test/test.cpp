#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "testFiles/linkedcard.h"
#include "testFiles/memory.h"
#include "testFiles/mockSendMessages.h"
#include "testFiles/mockReceiveMessages.h"

using namespace ::testing; 
using std::string;
using std::cout;
using std::endl;

TEST(ManejoDeTarjetas, AnadirTarjetas) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_STREQ("data", linkedcard->getData(2));
    EXPECT_EQ(1, linkedcard->getID(2));

    EXPECT_STREQ("data1", linkedcard->getData(1));
    EXPECT_EQ(2, linkedcard->getID(1));

    EXPECT_STREQ("data12", linkedcard->getData(0));
    EXPECT_EQ(3, linkedcard->getID(0));

    linkedcard->deleteLastData();
    linkedcard->deleteLastData();
    linkedcard->deleteLastData();

    delete linkedcard;
}

TEST(ManejoDeTarjetas, ObtenerDatosTarjetas) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_STREQ("data", linkedcard->getData(2));
    EXPECT_STREQ("data1", linkedcard->getData(1));
    EXPECT_STREQ("data12", linkedcard->getData(0));

    linkedcard->deleteLastData();
    linkedcard->deleteLastData();
    linkedcard->deleteLastData();

    delete linkedcard;
}

TEST(ManejoDeTarjetas, ObtenerIdentificacionTarjetas) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_EQ(1, linkedcard->getID(2));
    EXPECT_EQ(2, linkedcard->getID(1));
    EXPECT_EQ(3, linkedcard->getID(0));

    linkedcard->deleteLastData();
    linkedcard->deleteLastData();
    linkedcard->deleteLastData();

    delete linkedcard;
}

TEST(ManejoDeTarjetas, BuscarSiExisteTarjetaPorIdentificion) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_TRUE(linkedcard->searchForID(1));
    EXPECT_TRUE(linkedcard->searchForID(2));
    EXPECT_TRUE(linkedcard->searchForID(3));
    EXPECT_FALSE(linkedcard->searchForID(4));

    linkedcard->deleteLastData();
    linkedcard->deleteLastData();
    linkedcard->deleteLastData();

    delete linkedcard;
}

TEST(ManejoDeTarjetas, EliminarTarjetaPorIndice) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_EQ(0, linkedcard->deleteData(20));
    EXPECT_EQ(0, linkedcard->deleteData(-20));

    EXPECT_EQ(1, linkedcard->deleteData(2));
    EXPECT_EQ(1, linkedcard->deleteData(1));
    EXPECT_EQ(1, linkedcard->deleteData(0));

    EXPECT_EQ(-1, linkedcard->deleteData(20));
    EXPECT_EQ(-1, linkedcard->deleteData(-20));

    delete linkedcard;
}

TEST(ManejoDeTarjetas, EliminarLaUltimaTarjeta) {
    linkedCard *linkedcard = new linkedCard();

    linkedcard->add("data", 4, 1);
    linkedcard->add("data1", 5, 2);
    linkedcard->add("data12", 6, 3);

    EXPECT_TRUE(linkedcard->searchForID(1));
    linkedcard->deleteLastData();
    EXPECT_FALSE(linkedcard->searchForID(1));

    EXPECT_TRUE(linkedcard->searchForID(2));
    linkedcard->deleteLastData();
    EXPECT_FALSE(linkedcard->searchForID(2));

    EXPECT_TRUE(linkedcard->searchForID(3));
    linkedcard->deleteLastData();
    EXPECT_FALSE(linkedcard->searchForID(3));

    delete linkedcard;
}

TEST(HerramientasDeJuego, CrearMatrizAleatoria) {
    Memory *memory = new Memory();
    memory->randomCards();
    int value = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            value = memory->cardsMatrix[i][j];
            EXPECT_TRUE((value >= 0) && (value <= 15));   
        }
    }
    delete memory;    
}

TEST(ControlDeLaPartida, CambiarTurno) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(2))
        .WillRepeatedly(Return(true));

    int turn = memory.game->getTurn();   

    EXPECT_EQ(turn, -1);
    
    memory.changeTurn();
    turn = memory.game->getTurn();

    EXPECT_EQ(turn, 0);

    memory.changeTurn();
    turn = memory.game->getTurn();

    EXPECT_EQ(turn, 1);

    memory.game->setPlaying(true);

    memory.changeTurn();
    memory.changeTurn();

    delete sendMessages;
}

TEST(ManejoDeTarjetas, AgregarNuevaTarjetaEnMemoria) {
    Memory memory;

    char* data;

    memory.newCard(0);
    data = memory.inMemoryCards.getData(0);
    EXPECT_STREQ(data, "images/0.jpg");

    memory.newCard(14);
    data = memory.inMemoryCards.getData(0);
    EXPECT_STREQ(data, "images/14.jpg");
}

TEST(ManejoDeTarjetas, ObtenerBytesTarjeta) {
    Memory memory;

    char* data;

    memory.inMemoryCards.add("data", 4, 1);
    memory.cardsMatrix[2][2] = 1;
    data = memory.getAnyCard(2, 2);
    EXPECT_STREQ(data, "data");

    memory.cardsMatrix[3][3] = 2;
    data = memory.getAnyCard(3, 3);
    EXPECT_STREQ(data, "images/2.jpg");
}

TEST(ComunicacionServerClientes, EnviarTarjetasIndicadorasAEnemigo) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(8))
        .WillRepeatedly(Return(true));

    memory.sendEnemyOneIndicator(1, 0, 1);
    memory.sendEnemyOneIndicator(0, 1, 1);

    delete sendMessages;
}

TEST(ComunicacionServerClientes, EnviarTarjetasIndicadorasAJugador) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(4))
        .WillRepeatedly(Return(true));

    memory.sendPlayerOneIndicator(1, 0);
    memory.sendPlayerOneIndicator(0, 1);    

    delete sendMessages;
}

TEST(ComunicacionServerClientes, EnviarResultados) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    memory.game->setPlaying(true);
    memory.game->setTurn(1);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(18))
        .WillRepeatedly(Return(true));

    memory.sendResult(true, 1);
    memory.sendResult(false, 0);
    
    delete sendMessages;
}

TEST(ComunicacionServerClientes, EnviarGanandorYPerdedor) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    memory.game->setPlaying(true);
    memory.inGameCards = 0;

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(4))
        .WillRepeatedly(Return(true));

    memory.verifyInGameCards();
    
    delete sendMessages;
}

TEST(ManejoDeTarjetas, RecalcularTarjetasEnMemoria) {
    Memory memory;

    for (int i = 0; i < 5; i++) {
        memory.inMemoryCards.add("data", 4, i);
    }

    int size;

    while(memory.inGameCards != 4) {
        memory.inGameCards--;
        memory.recalculateInMemoryCards();
        size = memory.inMemoryCards.getSize();
        EXPECT_EQ(size, (memory.inGameCards / 3));
    }
}

TEST(ComunicacionServerClientes, EnviarPuntaje) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(16))
        .WillRepeatedly(Return(true));

    int score;

    memory.sendPoints(0);

    score = memory.game->getScore(0);
    EXPECT_EQ(score, 20);

    memory.pageHitCard = true;
    memory.sendPoints(1);

    score = memory.game->getScore(1);
    EXPECT_EQ(score, 40);

    memory.doublePointsPU = true;
    memory.sendPoints(0);

    score = memory.game->getScore(0);
    EXPECT_EQ(score, 60);
    
    memory.pageHitCard = true;
    memory.doublePointsPU = true;
    memory.sendPoints(1);

    score = memory.game->getScore(1);
    EXPECT_EQ(score, 120);
    
    delete sendMessages;
}

TEST(InteraccionesClientes, GuardarBotonesSeleccionados) {
    Memory memory;
    memory.lastClientsButtons(20);
    memory.lastClientsButtons(15);

    EXPECT_EQ(memory.buttonsSelected[0], 20);
    EXPECT_EQ(memory.buttonsSelected[1], 15);
}

TEST(ComunicacionServerClientes, EnviarTarjetasSeleccionadasAmbos) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(12))
        .WillRepeatedly(Return(true));

    memory.sendPlayersCard("data", 0);
    memory.sendPlayersCard("data", 1);

    delete sendMessages;
}

TEST(ComunicacionServerClientes, EnviarImagenQuestion) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(4))
        .WillRepeatedly(Return(true));

    memory.sendQuestionImages();

    delete sendMessages;
}

TEST(ComunicacionServerClientes, IntercambioDeNombres) {
    Memory memory;
    MockSendMessages *sendMessages = new MockSendMessages;
    memory.server = new Server(sendMessages);

    EXPECT_CALL(*sendMessages, send)
        .Times(AtLeast(4))
        .WillRepeatedly(Return(true));

    memory.sendPlayersName();

    delete sendMessages;
}

TEST(ComunicacionServerClientes, ObtenerAccionesClientes) {
    Memory memory;
    MockReceiveMessages *mockReceiveMessages = new MockReceiveMessages;
    memory.server = new Server(mockReceiveMessages);

    EXPECT_CALL(*mockReceiveMessages, recv)
        .Times(AtLeast(7))
        .WillRepeatedly(Return(4));

    memory.server->buffer = "name";
    memory.server->readClient(1);
    EXPECT_STREQ(memory.server->name, "name");
    EXPECT_TRUE(memory.server->newName);

    memory.server->buffer = "card";
    memory.server->readClient(1);
    EXPECT_EQ(memory.server->cardPetition, 4);
    EXPECT_TRUE(memory.server->newCardPetition);
    EXPECT_EQ(memory.server->clientPetition, 1);

    memory.server->buffer = "pu1";
    memory.server->readClient(1);
    EXPECT_EQ(memory.server->powerUpSelected, 1);
    EXPECT_EQ(memory.server->clientPowerUp, 1);

    memory.server->buffer = "pu2";
    memory.server->readClient(1);
    EXPECT_EQ(memory.server->powerUpSelected, 2);
    EXPECT_EQ(memory.server->clientPowerUp, 1);

    memory.server->buffer = "pu3";
    memory.server->readClient(1);
    EXPECT_EQ(memory.server->powerUpSelected, 3);
    EXPECT_EQ(memory.server->clientPowerUp, 1);
    

    delete mockReceiveMessages;
}