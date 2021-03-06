//
// Created by Patricio Araya on 12/4/18.
//

#include <fstream>
#include <sstream>
#include <random>
#include "Sistema.h"
#include <time.h>
#include <stdlib.h>



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

       /*Imprime los archivos validos encontrados, TODO:borrar al terminar
       for(int i = 0; i<cantNiveles;i++){
           cout<< niveles[i].nombre <<" : "<< niveles[i].dificultad << endl;
       }
        */
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

    cargarNivelesDisponibles();

    int command=0;

    while(command !=3){
        cout << "Menu:" << endl;
        cout << "[1] Iniciar Partida" << endl;
        cout << "[2] Estadisticas" << endl;
        cout << "[3] Salir" << endl;
        cout << "Elija una opción."<<endl;
        cin >> command;

        system("cls");
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
                    system("cls");
                    switch (command2) {
                        case 1:

                            partida("facil");
                            break;
                        case 2:

                            partida("medio");
                            break;
                        case 3:

                            partida("dificil");
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
                    system("cls");

                    switch (command3) {
                        case 1:
                            //Estadistica nivel facil
                            for(int i=0 ; i<cantNiveles ; i++){
                               if(niveles[i].dificultad == "facil"){
                                   victoriasFacil += niveles[i].victorias;
                               }
                            }
                            cout << "Cantidad de victorias modo facil:  " << victoriasFacil;
                            cout << "" << endl;
                            //Cantidad de victorias modo facil
                            break;
                        case 2:
                            //Estadistica nivel medio
                            for(int i=0 ; i<cantNiveles ; i++){
                                if(niveles[i].dificultad == "medio"){
                                    victoriasMedio += niveles[i].victorias;
                                }
                            }
                            cout << "Cantidad de victorias modo intermedio:  " << victoriasMedio;
                            cout << "" << endl;

                            break;
                        case 3:
                            //Estadisticas nivel dificil
                            for(int i=0 ; i<cantNiveles ; i++){
                                if(niveles[i].dificultad == "dificil"){
                                    victoriasDificil += niveles[i].victorias;
                                }
                            }
                            cout << "Cantidad de victorias modo dificil:  " << victoriasDificil;
                            cout << "" << endl;

                            break;
                        case 4:
                            //Estadisticas partidas jugadas
                            cout << "Cantidad de partidas jugadas:  " << partidasJugadas;
                            cout << "" << endl;

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
                generarEstadisticas();
                system("cls");
                break;
            default:
                cout << "Ingrese una opción válida" << endl;
                break;
        }
    }

}

Nivel* Sistema::nivelRandom(string dificultad) {


    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<std::mt19937::result_type> rand(1,cantNiveles);

    while(true) {
        int random = 0;

        random = rand(rng);

        if(niveles[random].dificultad == dificultad){

            return &niveles[random];
        }

    }


}

void Sistema::partida(string dificultad) {

    //Este metodo debe encargarse de toda la logica de la partida

    //Se aumenta en uno el contador de partidas
    partidasJugadas++;

    //Se carga el nivel
    Nivel *nivptr = nivelRandom(dificultad);
    cargarNivel(*nivptr);


    //Se presentan las reglas
    cout << "Bienvenido a Buscaminas"<<endl;
    cout << "Ingrese sus coordenadas siguiendo el siguiente esquema"<< endl;
    cout << "Primero ingrese la letra de la accion a realizar"<< endl;
    cout << "A: Destapa una celda"<< endl;
    cout << "B: Coloca una bandera"<< endl;
    cout << "?: Marca una casilla como sospechosa"<< endl;
    cout << "Luego ingrese 'F' mas el numero de la fila en que desea realizar la accion "<< endl;
    cout << "Despues 'C' mas el numero de la columna donde quiere realizar la accion"<< endl;
    cout <<"Recuerde separar cada termino usando ',' EJ:A,F2,C3" << endl;

    bool gameOver = false;
    while(!gameOver) {
        matrizJugador.printMatriz();
        cout << "Ingrese su accion seguida de las coordenadas de la misma" << endl;
        string userInput;
        cin >> userInput;
        system("cls");
        Comando accion = verificarAccion(userInput);

        if(accion.accion != '!'){
            //Significa que la accion es valida
            if(accion.accion == 'A'){
                //Se esta intentando destapar una celda, esta es la unica accion que realiza
                //cambios en la matrizJuego por lo que necesita atencion especial
                gameOver = destaparCelda(accion.fila, accion.columna);
            }
            else{
                //La accion es solo un indicador, se modifica la matriz de cara al jugador solamente
                matrizJugador.deleteNode(accion.fila,accion.columna);
                matrizJugador.addNode(accion.accion,accion.fila,accion.columna);
            }
        }
        //Accion no valida, se repite el ciclo
    }

    //Se termino el juego, si no quedan casillas descubiertas, significa que se gano la partida

    if(matrizJugador.getNode('H') == nullptr){
        nivptr->victorias++;
        cout << "Victoria" << endl;
    }
    //Si no, se termino el juego debido a la explosion de una bomba

}

Comando Sistema::verificarAccion(string input) {

    Comando com;
    com = {'!',0,0};

    if(input[0] == 'a' || input[0] == 'A'){

        com.accion = 'A';
    }
    else if(input[0] == 'b' || input[0] == 'B'){
        com.accion = 'B';
    }
    else if(input[0] == '?'){
        com.accion = '?';
    }
    else{
        //Accion no valida
        cout << "Comando invalido"<<endl;
        com = {'!',0,0};
        return com;
    }
    //Accion valida
    stringstream ss (input);
    string accion;
    string fila;
    string columna;

    getline(ss,accion,',');
    getline(ss,fila,',');
    getline(ss,columna,',');

    if(fila[0] == 'f' || fila[0]=='F'){
        //Fila es valida
        fila = fila.substr(1);
        //Ahora tengo aislado el numero de la fila y lo paso al comando
        com.fila = stoi(fila);
    }
    if(columna[0] == 'c' || columna[0]=='C') {
        //Columna es valida;
        columna = columna.substr(1);
        //Ahora tengo aislado el numero de la columna y lo paso al comando
        com.columna = stoi(columna);
    }

    //Ya deberia tener un comando valido, ahora verificar que este dentro del rango del tablero

    if(com.fila > 0 && com.fila < matrizJuego.getFilas()+1){
        if(com.columna >0 && com.columna < matrizJuego.getColumnas()+1){
            //Comando Valido, verificar que no sea una accion repetida
            if(matrizJugador.getNode(com.fila,com.columna)->getValue() == 'H'){
                cout<< "Comando valido: "<< com.accion<<":F"<<com.fila<<":C"<<com.columna<<endl;
                return com;
            }
            else {
                cout << "Coordenadas repetidas, ingrese otra casilla" << endl;
                return com;
            }
        }
        else{
            //Comando invalido
            cout << "Coordenadas fuera de rango, ingrese otra vez"<<endl;
            com = {'!',0,0};
            return com;
        }
    }
    else{
        //Comando invalido
        cout << "Comando invalido"<<endl;
        com = {'!',0,0};
        return com;
    }
}

bool Sistema::destaparCelda(int fila, int columna) {

    if(matrizJuego.getNode(fila,columna) != nullptr) {

        if (matrizJuego.getNode(fila, columna)->getValue() == 'X') {
            //Se encontro una mina
            cout << "BOOM!! Se termino el juego :(" << endl;
            //Actualizar la matriz del jugador
            matrizJugador.deleteNode(fila, columna);
            matrizJugador.addNode('X', fila, columna);
            matrizJugador.printMatriz();
            return true;
        }
        else if (matrizJuego.getNode(fila, columna)->getValue() != 'X') {
            //Se encontro un numero, actualizar matriz del jugador
            matrizJugador.deleteNode(fila, columna);
            matrizJugador.addNode(matrizJuego.getNode(fila, columna)->getValue(), fila, columna);
            return false;
        }
    }

    //Destapar celda y revisar las de alrededor
    destaparCeldaRec(fila,columna);

    return false;
}

void Sistema::destaparCeldaRec(int fila, int columna) {



    if(fila <= 0){
        return;
    }
    else if(fila > matrizJuego.getFilas()-1){
        return;
    }
    else if (columna <= 0){
        return;
    }
    else if(columna > matrizJuego.getColumnas()-1){
        return;
    }
    else if(matrizJugador.getNode(fila,columna)->getValue() != 'H'){
        return;
    }


    if(matrizJuego.getNode(fila,columna) != nullptr){

        if (matrizJuego.getNode(fila, columna)->getValue() == 'X') {
            //Se encontro una mina, no destapar
            return;
        }
        else if (matrizJuego.getNode(fila, columna)->getValue() != 'X') {
            //Se encontro un numero, actualizar matriz del jugador, destapar
            matrizJugador.deleteNode(fila, columna);
            matrizJugador.addNode(matrizJuego.getNode(fila, columna)->getValue(), fila, columna);
            return;
        }
    }
    else{

        matrizJugador.deleteNode(fila,columna);
        matrizJugador.addNode('0',fila,columna);


        destaparCeldaRec(fila-1,columna-1);
        destaparCeldaRec(fila-1,columna);
        destaparCeldaRec(fila-1,columna+1);
        destaparCeldaRec(fila,columna-1);
        destaparCeldaRec(fila,columna+1);
        destaparCeldaRec(fila+1,columna-1);
        destaparCeldaRec(fila+1,columna);
        destaparCeldaRec(fila+1,columna+1);
    }

}

void Sistema::generarEstadisticas() {


    victoriasFacil = 0;
    victoriasMedio = 0;
    victoriasDificil = 0;

    for(int i=0 ; i<cantNiveles ; i++){
        if(niveles[i].dificultad == "facil"){
            victoriasFacil += niveles[i].victorias;
        }
        else if(niveles[i].dificultad == "medio"){
            victoriasMedio += niveles[i].victorias;
        }
        if(niveles[i].dificultad == "dificil"){
            victoriasDificil += niveles[i].victorias;
        }


    }

    ofstream archivo;
    archivo.open("../archivos/estadisticas.txt",ios::trunc);
    archivo<<"Cantidad de partidas jugadas:" << partidasJugadas<<endl;
    archivo<<"Victorias nivel facil:" << victoriasFacil<<endl;
    archivo<<"Victorias nivel intermedio:" << victoriasMedio<<endl;
    archivo<<"Victorias nivel dificil:" << victoriasDificil<<endl;

    archivo.close();


}


Sistema::~Sistema() = default;

