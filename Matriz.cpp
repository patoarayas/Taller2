//
// Created by Patricio Araya on 12/4/18.
//

#include "Matriz.h"
#include <iostream>

using namespace std;

Matriz::Matriz() = default;

Matriz::Matriz(int filas, int columnas) {
    this->vectorFilas = new Nodo [filas];
    this->vectorColumnas = new Nodo[columnas];
    for(int i=0 ; i<filas ; i++){
        vectorFilas[i].setColumna(0);
        vectorFilas[i].setValue();
        vectorFilas[i].setNext(&vectorFilas[i]);
    }
    for(int i=0 ; i<columnas ; i++){
        vectorColumnas[i].setFila(0);
        vectorColumnas[i].setValue();
        vectorColumnas[i].setUp(&vectorColumnas[i]);
    }
    this->filas=filas;
    this->columnas=columnas;
}

bool Matriz::addNode(char valor, int fila, int columna) {
    Nodo* current = &vectorFilas[fila-1];

    while(current->getNext()!=&vectorFilas[fila-1]&&current->getNext()->getColumna()>columna){
        current = current->getNext();
    }
    if(current->getNext()->getColumna()==columna){
        //No se puede reemplazar, ya hay un nodo en esta posición, elimÌnelo primero
        return false;
    }else if(current->getNext()->getColumna()<columna) {
        Nodo* nodo = new Nodo(valor);
        nodo->setNext(current->getNext());
        current->setNext(nodo);
        nodo->setColumna(columna);
        current = &vectorColumnas[columna-1];
        while(current->getUp()!=&vectorColumnas[columna-1]&&current->getUp()->getFila()>fila){
            current = current->getUp();
        }
        if(current->getUp()->getFila()==fila){
            //No se puede reemplazar, ya hay un nodo en esta posición, elimÌnelo primero
            return false;
        }else if(current->getUp()->getFila()<fila) {
            nodo->setUp(current->getUp());
            current->setUp(nodo);
            nodo->setFila(fila);
            current = nullptr;
            delete current;
        }else{
            return false;
        }
    }else{
        return false;
    }

    return false;
}


bool Matriz::deleteNode(int fila, int columna) {
    Nodo* current = &vectorFilas[fila-1];

    while(current->getNext()!=&vectorFilas[fila-1]&&current->getNext()->getColumna()>columna){
        current = current->getNext();
    }
    if(current->getNext()->getColumna()==columna){
        Nodo* aux = current->getNext();
        current->setNext(current->getNext()->getNext());
        aux->setNext(nullptr);
        current = &vectorColumnas[columna-1];
        while(current->getUp()!=&vectorColumnas[columna-1]&&current->getUp()->getFila()>fila){
            current = current->getUp();
        }
        if(current->getUp()->getColumna()==columna){
            current->setUp(current->getUp()->getUp());
            aux->setUp(nullptr);
            current = nullptr;
            delete current;
            delete aux;
            return true;
        }else if(current->getUp()->getFila()<fila) {
            return false;
        }else{
            return false;
        }
    }else if(current->getNext()->getColumna()<columna) {
        //No existe nodo en esta posición
        return false;
    }else{
        return false;
    }
}

Nodo *Matriz::getNode(int fila, int columna) {
    Nodo* current = &vectorFilas[fila-1];

    while(current->getNext()!=&vectorFilas[fila-1]&&current->getNext()->getColumna()>columna){
        current = current->getNext();
    }
    if(current->getNext()->getColumna()==columna){
        return current->getNext();
    }else if(current->getNext()->getColumna()<columna) {
        //No existe  nodo en esta posición
        return nullptr;
    }else {
        return nullptr;
    }
}

bool Matriz::deleteNode(char valor) {

    bool verify = false;
    Nodo* node;
    for(int i=0 ; i<filas ; i++){

        for(node = &vectorFilas[i] ; node->getNext() != &vectorFilas[i] ; node = node->getNext()) {
            if (node->getNext()->getValue() == valor) {
                deleteNode(node->getNext()->getFila(), node->getNext()->getColumna());
                verify = true;
            }
        }
    }

    return verify;

}

Nodo *Matriz::getNode(char valor) {
    Nodo* node;
    for(int i=0 ; i<filas ; i++){

        for(node = &vectorFilas[i] ; node->getNext() != &vectorFilas[i] ; node = node->getNext()) {
            if (node->getNext()->getValue() == valor) {
                return node->getNext();
            }
        }
    }
    return nullptr;
}

Nodo *Matriz::popNode(int fila, int columna) {
    Nodo* current = &vectorFilas[fila-1];

    while(current->getNext()!=&vectorFilas[fila-1]&&current->getNext()->getColumna()>columna){
        current = current->getNext();
    }
    if(current->getNext()->getColumna()==columna){
        Nodo* aux = current->getNext();
        current->setNext(current->getNext()->getNext());
        aux->setNext(nullptr);
        current = &vectorColumnas[columna-1];
        while(current->getUp()!=&vectorColumnas[columna-1]&&current->getUp()->getFila()>fila){
            current = current->getUp();
        }
        if(current->getUp()->getColumna()==columna){
            current->setUp(current->getUp()->getUp());
            aux->setUp(nullptr);
            current = nullptr;
            delete current;
            return aux;
        }else if(current->getUp()->getFila()<fila) {
            return nullptr;
        }else{
            return nullptr;
        }
    }else if(current->getNext()->getColumna()<columna) {
        //No existe alg˙n nodo en esta posiciÛn
        return nullptr;
    }else{
        return nullptr;
    }
}

void Matriz::printMatriz() {
    cout << "       ";
    for(int j=1 ; j < columnas+1 ; j++){
        cout << "";
        cout << "[C";
        cout << j;
        cout << "]";
        if(j==columnas){
            cout << "" << endl;
        }
    }
    for(int i=1 ; i<filas+1 ; i++){
        cout << "[F";
        cout << i;
        cout << "]";
        cout << " ";
        for(int j=1 ; j<columnas+1; j++){
            if(j==columnas){
                cout << "   ";
                if(getNode(i,j)== nullptr){
                    cout << "0" << endl;
                }else{
                    cout << getNode(i,j)->getValue() << endl;
                }
            }else{
                cout << "   ";
                if(getNode(i,j)== nullptr){
                    cout << "0";
                }else{
                    cout << getNode(i,j)->getValue();
                }
            }
        }
    }
}

Matriz::~Matriz() {
    //TODO: Revisar destructor
    //delete [] vectorFilas;
    //delete [] vectorColumnas;
}