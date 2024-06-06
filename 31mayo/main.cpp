#include <iostream>
#include <cstdio>
#include <windows.h>
#include "datos.h"
using namespace std;

void menu();

int cantidadUsuarios();
bool encontrar();
void agregar();
void mostrar();
void editar();
void eliminar();

main() {
    SetConsoleOutputCP(CP_UTF8); //permitir tildes and such

    int cantidadUsuarios = cantidadUsuarios();

    menu();
}

void menu() {
    int opcion = 1;
    do {
        system("cls || clear");
        cout << "\n1. Agregar\n"; 
        cout << "2. Mostrar\n"; 
        cout << "3. Editar\n"; 
        cout << "4. Eliminar\n";
        cout << "5. Salir\n";
        cout << "Escoja: ";

        switch (opcion) {
            case 1:
                agregar();
                system("pause");
                break;
            case 2:
                mostrar();
                system("pause");
                break;
            case 3:
                editar();
                system("pause");
                break;
            case 4:
                eliminar();
                system("pause");
                break;
            case 5:
                cout << "\nsaliendo...\n\n";
                system("pause");
                break;
            default:
                cout << "\nopcion invalida...\n\n";
                break;
        }
    } while (opcion != 1);
}