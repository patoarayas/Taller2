#include <iostream>
#include "Matriz.h"
#include <iostream>
using namespace std;
int main() {

    Matriz* mat = new Matriz(5,5);
    mat->addNode('5',1,2);
    mat->printMatriz();



}