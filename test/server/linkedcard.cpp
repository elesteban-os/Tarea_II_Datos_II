#include "linkedcard.h"
/**
 * @brief Construct a new linked Card::linked Card object
 * 
 */
linkedCard::linkedCard()
{

}

/**
 * @brief Añade una nueva tarjeta a la lista.
 * 
 * @param data char array de la imagen.
 * @param size tamaño del char array.
 * @param num identificación de la tarjeta.
 */
void linkedCard::add(char* data, int size, int num) {
    if (head == NULL) {
        head = new card(data, size, num);
    } else {
        card *tmp = head;
        head = new card(data, size, num);
        head->setNext(tmp);
    }
    this->size++;
}

/**
 * @brief Obtiene la imagen de la tarjeta.
 * 
 * @param index posición de la tarjeta.
 * @return char array de la imagen de la tarjeta.
 */
char* linkedCard::getData(int index) {
    if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->getNext();
        }
        return tmp->getImage();
    } else {
        return NULL;
    }
}

/**
 * @brief Obtiene la identificación de una tarjeta.
 * 
 * @param index posición de la tarjeta.
 * @return identificación de la tarjeta.
 */
int linkedCard::getID(int index) {
    if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->getNext();
        }
        return tmp->getID();
    } else {
        return -1;
    }
}

/**
 * @brief Busca si existe una tarjeta por medio de su identificación.
 * 
 * @param ID identificación de la tarjeta.
 * @return true si existe la tarjeta con esa identificación.
 */
bool linkedCard::searchForID(int ID) {
    card *tmp = head;
    for (int i = 0; i < size; i++) {
        if (tmp->getID() == ID) {
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

/**
 * @brief Obtiene la imagen de la tarjeta buscando con una identificación.
 * 
 * @param id identificación de la tarjeta.
 * @return char array de la imagen de la tarjeta.
 */
char* linkedCard::getDataByID(int id) {
    card *tmp = head;
    for (int i = 0; i < size; i++) {
        if (tmp->getID() == id) {
            return tmp->getImage();
        }
        tmp = tmp->getNext();
    }
    return NULL;
}

/**
 * @brief Elimina un elemento de la lista de tarjetas.
 * 
 * @param index posición del elemento.
 * @return 1 si el elemento se eliminó correcramente, 0 si no se eliminó nada.
 */
int linkedCard::deleteData(int index) {
    if (size == 1 && index == 0) {
        delete(head);
        size--;
        return 1;
    } else if (size == 0) {
        return -1;
    } else if (size == 2 && index == 1) {
        delete(head->getNext());
        head->setNext(NULL);
        size--;
        return 1;
    } else if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index - 1; i++) {
            tmp = tmp->getNext();
        }
        card *tmpNext = tmp->getNext()->getNext();
        delete(tmp->getNext());
        tmp->setNext(tmpNext);
        size--;
        return 1;
    }
    return 0;
}

/**
 * @brief Elimina el último elemento de la lista.
 * 
 */
void linkedCard::deleteLastData() {
    deleteData(size - 1);
}

/**
 * @brief Obtiene el valor del tamaño de la lista.
 * 
 * @return entero del tamaño de la lista.
 */
int linkedCard::getSize() {
    return size;
}
