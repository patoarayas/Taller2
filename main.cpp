#include <iostream>
#include "Matriz.h"
#include <iostream>
using namespace std;
int main() {

    auto * mat = new Matriz(5,5);
    mat->addNode('5',1,2);
    mat->printMatriz();
    cout << mat->getNode('5')->getFila() << endl;



}