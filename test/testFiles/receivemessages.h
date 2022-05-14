#ifndef RECEIVEMESSAGES_H
#define RECEIVEMESSAGES_H

#include <iostream>

class ReceiveMessages {
    public:
        virtual int recv(int socket, char* buffer, int size, int flags);
};

#endif // RECEIVEMESSAGES_H