//
// Created by Patricio Araya on 12/4/18.
//

#include <fstream>
#include <sstream>
#include <cstdlib>
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

    //ACA van lienas de codigo que estoy usando para testear otras cosas
    cargarNivel(niveles[3]);
    matrizJuego.printMatriz();
    matrizJugador.printMatriz();


    int command=0;

    while(command !=3){
        cout << "Menu:" << endl;
        cout << "[1] Iniciar Partida" << endl;
        cout << "[2] Estadisticas" << endl;
        cout << "[3] Salir" << endl;
        cout << "Elija una opción."<<endl;
        cin >> command;

        switch(command){
            case 1: {
                int command2 = 0;
                while (command2 != 4) {
                    cout << "---------------------" << endl;
                    cout << "[1] Dificultad Facil" << endl;
                    cout << "[2] Dificultad Intermedia" << endl;
                    cout << "[3] Dificultad Dificil" << endl;
                    cout << "[4] Volver al menu principal" << endl;
                    cout << "Elija una opción." << endl;
                    cin >> command2;
                    switch (command2) {
                        case 1:
                            cargarNivel(nivelRandom("facil"));
                            break;
                        case 2:
                            cargarNivel(nivelRandom("medio"));
                            break;
                        case 3:
                            cargarNivel(nivelRandom("dificil"));
                            break;
                        case 4:
                            //Volver al menu principal
                            break;
                        default:
                            cout << "Ingrese una opción válida" << endl;
                            break;
                    }
                }
                break;
            }
            case 2: {
                int command3 = 0;
                while (command3 != 5) {
                    cout << "------------------------------------------" << endl;
                    cout << "[1] Cantidad de victorias modo facil" << endl;
                    cout << "[2] Cantidad de victorias modo intermedio" << endl;
                    cout << "[3] Cantidad de victorias modo dificil" << endl;
                    cout << "[4] Cantidad de partidas jugadas" << endl;
                    cout << "[5] Volver al menu principal" << endl;
                    cout << "Elija una opción." << endl;
                    cin >> command3;
                    switch (command3) {
                        case 1:
                            //Cantidad de victorias modo facil
                            break;
                        case 2:
                            //Cantidad de victorias modo intermedio
                            break;
                        case 3:
                            //Cantidad de victorias modo dificil
                            break;
                        case 4:
                            //Cantidad de partidas jugadas
                            break;
                        case 5:
                            //Volver al menu principal
                            break;
                        default:
                            cout << "Ingrese una opción válida" << endl;
                            break;
                    }
                }
            }
                break;

            case 3:
                //Crear estadisticas.txt y salir
                break;
            default:
                cout << "Ingrese una opción válida" << endl;
                break;
        }
    }

}

Nivel Sistema::nivelRandom(string dificultad) {

    while(true) {
        int random = 0;
        random = rand()  % cantNiveles + 1;
        if(niveles[random].dificultad == dificultad){
            return niveles[random];
        }

    }


}

Sistema::~Sistema() = default;

