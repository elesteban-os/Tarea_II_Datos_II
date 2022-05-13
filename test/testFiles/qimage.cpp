#include "qimage.h"

QImage::QImage(char* addr) {
    this->imageBits = addr;
    this->sizeBits = strlen(addr);
}

char* QImage::bits() {
    return this->imageBits;
}

int QImage::sizeInBytes() {
    return this->sizeBits;
}