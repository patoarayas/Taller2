//
// Created by Patricio Araya on 12/4/18.
//

#ifndef TALLER2_SISTEMA_H
#define TALLER2_SISTEMA_H

#include "Matriz.h"
#include <iostream>

using namespace std;


/**
 * Struct que guarda los datos de los niveles
 */
struct Nivel{
    string nombre;
    string dificultad;
};

class Sistema {

private:
    //Matriz que muestra los datos al jugador
    Matriz matrizJugador;
    //MAtriz que contiene los datos del tablero
    Matriz matrizJuego;
    //Arreglo que guarda los niveles disponibles en el juego
    Nivel* niveles;
    //Cantidad de niveles disponibles
    int cantNiveles;





public:
    /**
     * Constructor vacio
     */
    Sistema();

    /**
     * Destructor
     */
    ~Sistema();

    //TODO: Falta implementar menu
    /**
     * Despliega el menu por pantalla
     */
    void menu();

    /**
     * Abre el archivo "Campos.txt" y verifica que niveles estan disponibles y los carga en el arreglo de niveles
     */
    void cargarNivelesDisponibles();

    /**
     *  En base a un nivel pasado por parametro, carga el mismo en las matrices correspondientes
     * @param nivel : Nivel que se desea cargar
     */
    void cargarNivel(Nivel nivel);

    //TODO: Falta implemetar el metodo nivelRandom()
    /**
     * En base a una dificultad dada, se selecciona un nivel al azar acorde con la misma
     * @param dificultad : Dificultad deseada
     * @return un nivel de juego
     */
    Nivel nivelRandom(string dificultad);


};


#endif //TALLER2_SISTEMA_H
