#ifndef MOCKSENDMESSAGES_H
#define MOCKSENDMESSAGES_H

#include "sendmessages.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


class MockSendMessages : public SendMessages {
    public:
        MOCK_METHOD(bool, send, (int client, const char* message, int size, int flags), (override)); 
};


#endif // MOCKSENDMESSAGES_H