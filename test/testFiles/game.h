#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string.h>

class Game
{
private:
    int scores[2] = {0, 0};
    char player1name[20];
    char player2name[20];
    bool playing;
    int turn = -1;

public:
    Game();
    int getScore(int player);
    void addScore(int player, int score);
    char* getPlayer1name();
    char* getPlayer2name();
    void setPlayer1name(char* name);
    void setPlayer2name(char* name);
    bool getPlaying();
    void setPlaying(bool value);
    int getTurn();
    void setTurn(int value);
};

#endif // GAME_H
