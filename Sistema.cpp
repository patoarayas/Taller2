//
// Created by Patricio Araya on 12/4/18.
//

#include <fstream>
#include <sstream>
#include "Sistema.h"

Sistema::Sistema() = default;

void Sistema::cargarNivelesDisponibles() {

    //Primero verificar que los archivos en "Campos.txt" existan

    ifstream campos;
    //Esta es la ruta relativa, funciona en unix, testear en windows
    campos.open("../archivos/Campos.txt");

    cantNiveles = 0;
    auto* auxNiveles = new Nivel[100];

    if(campos){
        cout << "Se estan cargando los niveles disponibles" << endl;
       while(!campos.eof()){

           string nombre;
           string dificultad;
           getline(campos, nombre,',' );
           getline(campos, dificultad);

           ifstream chequeo;
           chequeo.open("../archivos/"+nombre);

           if(chequeo) {
               //Archivo leido existe
               auxNiveles[cantNiveles] = {nombre, dificultad};
               cantNiveles++;

           }

           chequeo.close();
       }

       niveles = new Nivel[cantNiveles];

       for(int i = 0; i< cantNiveles; i++){
           niveles[i] = auxNiveles[i];
       }

       for(int i = 0; i<cantNiveles;i++){
           cout<< niveles[i].nombre <<" : "<< niveles[i].dificultad << endl;
       }

       campos.close();


    }
    else{
        cout << "No se encontro el archivo con la informacion de niveles" << endl;

    }

}

void Sistema::cargarNivel(Nivel nivel) {

    ifstream archNivel;
    archNivel.open("../archivos/"+nivel.nombre);

    if(archNivel){
        cout << "Cargando nivel deseado" << endl;

        //Tomo la primera linea del archivo con las dimensiones de la matriz
        string dimensiones;
        getline(archNivel,dimensiones);
        int filas;
        int columnas;

        if(dimensiones[0] == '9'){
            filas = 9;
            columnas = 9;
        }
        else{
            filas = stoi(dimensiones.substr(0,2));
            columnas = stoi(dimensiones.substr(3,4));
        }

        // Teniendo las dimensiones, procedo a crear las matrices

        matrizJugador =  Matriz(filas,columnas);
        matrizJuego = Matriz(filas,columnas);

        // Con las matrices creadas se procede a llenarlas
        // Primero llenamos la matrizJuego con los datos del archivo
        int contFila = 1;
        while(!archNivel.eof()){


            for(int i = 1; i<=columnas;i++){
                string s;
                if(i < columnas){
                    getline(archNivel,s,',');
                }
                else{
                    getline(archNivel,s);
                }


                if(s[0] != '0') {

                    matrizJuego.addNode(s[0], contFila, i);
                }

            }
            contFila++;


        }

        //MatrizJuego cargada

        //Ya con la matrizJuego cargada, preparar la matrizJugador

        for(int i = 1;i<=filas;i++){
            for(int j=1; j<=columnas;j++){

                matrizJugador.addNode('H',i,j);
            }
        }

    }
    else{
        cout << "Error al cargar el nivel" << endl;
    }

}

void Sistema::menu() {

    cargarNivel(niveles[3]);
    matrizJuego.printMatriz();
    matrizJugador.printMatriz();
}

Nivel Sistema::nivelRandom(string dificultad) {

    return {"NULL","NULL"};
}

Sistema::~Sistema() = default;

