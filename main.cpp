#include <iostream>
#include "Matriz.h"
#include "Sistema.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {

    Sistema sistema;
    sistema.cargarNivelesDisponibles();
    sistema.menu();


    return 0;



}