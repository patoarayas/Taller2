//
// Created by Patricio Araya on 12/4/18.
//

#ifndef TALLER2_NODO_H
#define TALLER2_NODO_H


class Nodo {

private:
    char value;
    int fila;
    int columna;
    Nodo* next;
    Nodo* up;

public:
    Nodo();
    Nodo(char value);
    Nodo* getUp();
    Nodo* getNext();
    char getValue();
    void setValue(char value);
    void setValue();
    void setColumna(int columna);
    void setFila(int fila);
    void setNext(Nodo* node);
    void setUp(Nodo* node);
    int getFila();
    int getColumna();
    ~Nodo();

};


#endif //TALLER2_NODO_H
