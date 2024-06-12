#include <iostream>

void Hola(std::string stringer) {
    if(stringer != "Hola") {
        std::cout << "Ok";
    } else {
        std::cout << "Camaron con Cola";
    }
}

int main() {
    std::string stringer;
    std::cout << "Ingrese un string: ";
    std::cin >> stringer;
    Hola(stringer);
}