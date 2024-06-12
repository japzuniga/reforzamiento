#include <iostream>
using namespace std;

int suma(int num1, int num2) {
    num1 = 8;
    return num1 + num2;
}

int resta(int *num1, int *num2) {
    *num1 = 6;
    return *num1 - *num2;
}

int main() {
    int num1, num2, resultado;
    cout << "Ingrese el primer número: ";
    cin >> num1;
    cout << "Ingrese el segundo número: ";
    cin >> num2;
    resultado = resta(&num1, &num2);
    cout << "La resta de " << num1 << " - " << num2 << " = " << resultado << endl;

    return 0;
}