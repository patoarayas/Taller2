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
    int victorias = 0;
};
/**
 * Struct que guarda los datos de un comando
 */
struct Comando{
    char accion;
    int fila;
    int columna;

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
    //Cantidad de partidas jugadas
    int partidasJugadas=0;





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


    /**
     * En base a una dificultad dada, se selecciona un nivel al azar acorde con la misma y lo retorna.
     * @param dificultad : Dificultad deseada
     * @return un nivel de juego
     */
    Nivel* nivelRandom(string dificultad);

    /**
     * Se encarga de la logica de la partida
     */
    void partida(string dificultad);
    /**
     * Retorna si el string entregado es una accion valida
     * @param in : el string a verificar
     * @return : estructura Comando si es valido, retorna un comando {!,0,0} si no;
     */
    Comando verificarAccion(string in);

    bool destaparCelda(int fila, int columna);

};


#endif //TALLER2_SISTEMA_H
