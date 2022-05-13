#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

class SendMessages {
    public:
        virtual bool send(int client, const char* message, int size, int flags);
};

#endif // SENDMESSAGES_H