#include <iostream>
using namespace std;

int mult(int num, int i) {
    return num*i;
}

main() {
    int i, num;
    cout << "ingresar un numero: ";
    cin >> num;

    while (i <= 12) {
        int resultado = mult(num, i);
        cout << num << " * " << i << " = " << resultado << endl;
        i++;
    }
}