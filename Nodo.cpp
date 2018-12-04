//
// Created by Patricio Araya on 12/4/18.
//

#include "Nodo.h"

Nodo::Nodo(){

}

Nodo::Nodo(char value) {
    this->up= nullptr;
    this->next= nullptr;
    this->fila= 0;
    this->columna=0;
    this->value=value;
}

Nodo *Nodo::getUp() {
    return this->up;
}

Nodo *Nodo::getNext() {
    return this->next;
}

char Nodo::getValue() {
    return this->value;
}

void Nodo::setValue(char value) {
    this->value=value;
}

void Nodo::setValue() {
    this->value= '0';
}

void Nodo::setColumna(int columna) {
    this->columna=columna;
}

void Nodo::setFila(int fila) {
    this->fila=fila;
}

void Nodo::setNext(Nodo *node) {
    this->next=node;
}

void Nodo::setUp(Nodo *node) {
    this->up=node;
}

int Nodo::getFila() {
    return this->fila;
}

int Nodo::getColumna() {
    return this->columna;
}

Nodo::~Nodo() {

}