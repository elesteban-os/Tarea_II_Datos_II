#include "card.h"

/**
 * @brief Construct a new card::card object.
 * 
 * @param image puntero a un char array de la imagen.
 * @param size tamaño del array de la imagen-
 * @param num identificación de la tarjeta.
 */
card::card(char *image, int size, int num)
{
    memcpy(imageBits, image, size);
    ID = num;
}

/**
 * @brief Construct a new card::card object
 * 
 */
card::card() {

}

/**
 * @brief obtiene el char array de la imagen.
 * 
 * @return retorna el char array de la imagen.
 */
char* card::getImage() {
    return imageBits;
}

/**
 * @brief coloca un valor de un char array de una imagen.
 * 
 * @param image puntero a un char array de la imagen.
 * @param size tamaño del array de la imagen.
 */
void card::setImage(char* image, int size) {
    memcpy(imageBits, image, size);
}

/**
 * @brief coloca la tarjeta siguiente.
 * 
 * @param next1 puntero a la siguiente tarjeta.
 */
void card::setNext(card *next1) {
    next = next1;
}

/**
 * @brief obtiene el puntero a la carta siguiente.
 * 
 * @return puntero a la carta siguiente.
 */
card* card::getNext() {
    return next;
}

/**
 * @brief Obtiene la identificación de la tarjeta.
 * 
 * @return retorna la identificación de la tarjeta.
 */
int card::getID() {
    return ID;
}

/**
 * @brief Coloca un valor a la identificación de la tarjeta.
 * 
 * @param num identificación de la tarjeta.
 */
void card::setID(int num) {
    ID = num;
}
