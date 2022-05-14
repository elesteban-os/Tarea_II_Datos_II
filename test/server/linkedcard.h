#ifndef LINKEDCARD_H
#define LINKEDCARD_H

#include "card.h"
#include <iostream>

class linkedCard
{
private:
    card *head = NULL;
    int size = 0;
public:
    linkedCard();
    void add(char* data, int size, int num);
    char* getData(int index);
    int deleteData(int index);
    void deleteLastData();
    int getSize();
    int getID(int index);
    bool searchForID(int ID);
    char* getDataByID(int id);
};

#endif // LINKEDCARD_H
