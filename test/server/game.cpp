#include "game.h"

/**
 * @brief Construct a new Game:: Game object
 * 
 */
Game::Game()
{

}

/**
 * @brief añade puntaje a un jugador.
 * 
 * @param player jugador.
 * @param score puntaje.
 */
void Game::addScore(int player, int score) {
    scores[player] += score;
}

/**
 * @brief Obtiene el nombre del jugador 1.
 * 
 * @return puntero a un char array de un nombre.
 */
char* Game::getPlayer1name() {
    return player1name;
}

/**
 * @brief Obtiene el nombre del jugador 2.
 * 
 * @return puntero a un char array de un nombre.
 */
char* Game::getPlayer2name() {
    return player2name;
}

/**
 * @brief Obtiene el puntaje de un jugador.
 * 
 * @param player jugador.
 * @return el puntaje.
 */
int Game::getScore(int player) {
    return scores[player];
}

/**
 * @brief Coloca el nombre del jugador 1.
 * 
 * @param name puntero del nombre del jugador.
 */
void Game::setPlayer1name(char *name) {
    memcpy(player1name, name, strlen(name));
}

/**
 * @brief Coloca el nombre del jugador 2.
 * 
 * @param name puntero del nombre del jugador.
 */
void Game::setPlayer2name(char *name) {
    memcpy(player2name, name, strlen(name));
}

/**
 * @brief Obtiene el estado de la inicializción del juego.
 * 
 * @return el estado del juego.
 */
bool Game::getPlaying() {
    return this->playing;
}

/**
 * @brief Coloca el estado de la inicializción del juego.
 * 
 * @param value valor del estado del juego-
 */
void Game::setPlaying(bool value) {
    this->playing = value;
}

/**
 * @brief Obtiene el turno.
 * 
 * @return el turno.
 */
int Game::getTurn() {
    return this->turn;
}

/**
 * @brief coloca el turno del jugador.
 * 
 * @param value turno del jugador.
 */
void Game::setTurn(int value) {
    this->turn = value;
}
 
