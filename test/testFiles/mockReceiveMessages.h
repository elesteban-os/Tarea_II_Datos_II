#ifndef MOCKRECEIVEMESSAGES_H
#define MOCKRECEIVEMESSAGES_H

#include "receivemessages.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


class MockReceiveMessages : public ReceiveMessages {
    public:
        MOCK_METHOD(int, recv, (int socket, char* buffer, int size, int flags), (override)); 
};

#endif // MOCKRECEIVEMESSAGES_H