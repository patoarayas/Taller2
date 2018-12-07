//
// Created by Patricio Araya on 12/4/18.
//

#ifndef TALLER2_MATRIZ_H
#define TALLER2_MATRIZ_H
#include "Nodo.h"

class Matriz {

private:
    Nodo *vectorFilas;
    Nodo *vectorColumnas;
    int filas;
    int columnas;

public:
    /**
     * Constructor vacio
     */
    Matriz();

    /**
     * Constructor de la matriz
     * @param filas : Cantidad de filas (int)
     * @param columnas : Cantidad de columnas (int)
     */
    Matriz(int filas, int columnas);

    /**
     * Agrega un nodo a la matriz
     * @param valor : Valor del nodo a agregar (char)
     * @param fila : Fila en que se agrega el nuevo nodo
     * @param columna : Columna en que se agrega el nuevo nodo
     * @return booleano que indica el resultado de la operación
     */
    bool addNode(char valor, int fila, int columna);

    /**
     * Borra un nodo de la matriz en base a su posición
     * @param fila : Fila del nodo a eliminar
     * @param columna : Columna del nodo a eliminar
     * @return booleano que indica el resultado de la operación
     */
    bool deleteNode(int fila, int columna);

    /**
     * Retorna un nodo en base a su posición
     * @param fila : La fila del nodo a retornar
     * @param columna : La columnda del nodo a retornar
     * @return el nodo deseado
     */
    Nodo* getNode(int fila , int columna);

    /**
     *  Borra un nodo de la matriz en base a su valor
     * @param valor : Valor del nodo a eliminar
     * @return  booleano que indica el resultado de la operación
     */
    bool deleteNode(char valor);

    /**
     * Retorna un nodo en base a su valor
     * @param valor
     * @return el nodo deseado
     */
    Nodo* getNode(char valor);

    /***
     * Elimina y retorna un nodo dada su posicion
     * @param fila
     * @param columna
     * @return el nodo eliminado
     */
    Nodo* popNode(int fila, int columna);

    /**
     * Despliega la matriz por consola
     */
    void printMatriz();

    int getFilas();
    int getColumnas();
    /**
     * Destructor
     */
    ~Matriz();
};


#endif //TALLER2_MATRIZ_H
