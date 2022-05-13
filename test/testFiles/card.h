#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string.h>

class card
{
private:
    char imageBits[202500];
    int ID = 0;
    card *next = NULL;
public:
    card(char* image, int size, int num);
    card();
    char* getImage();
    int getID();
    void setID(int num);
    void setImage(char* image, int size);
    void setNext(card *next1);
    card* getNext();
};

#endif // CARD_H
