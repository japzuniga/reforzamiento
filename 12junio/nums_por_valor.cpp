#include <iostream>
using namespace std;

void pedirNum(int num) {
    cout << "ingresar num 2, electric boogaloo: ";
    cin >> num;
    cout << "num 2: " << num;
}

main() {
    int num;
    cout << "ingresar num: ";
    cin >> num;

    pedirNum(num);

    cout << "\nnum 1: " << num;
}