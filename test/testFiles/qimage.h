#ifndef QIMAGE_H
#define QIMAGE_H

#include <string.h>

class QImage {
    private:
        int sizeBits;
        char* imageBits;
    public:
        QImage(char* addr);
        int sizeInBytes();
        char* bits();
};

#endif // QIMAGE_H