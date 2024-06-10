#include <iostream>
#include "functions.cpp"
using namespace std;

main() {
    int option;
    do {
        system("cls || clear");
        cout << "\n\t\t\tBook Catalogue:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Add book(s)\n";
        cout << "2. Show all books\n";
        cout << "3. Show recent books\n";
        cout << "4. Update book information\n";
        cout << "5. Delete book from catalogue\n";
        cout << "6. Exit\n";
        cout << "Enter: ";
        cin >> option;
    
        switch (option) {
            case 1:
                int amount;
                cout << "\nHow many books do you wish to register? ";
                cin >> amount;
                addBooks(amount);
                system("pause");
                break;
            case 2:
                system("cls || clear");
                showBooks();
                system("pause");
                break;
            case 3:
                int x;
                cout << "\nHow recent do you wish the books shown to be? (in years) ";
                cin >> x;
                show_last_x_years(x);
                system("pause");
                break;
            case 4:
                system("cls || clear");
                updateBook();
                system("pause");
                break;
            case 5:
                system("cls || clear");
                deleteBook();
                system("pause");
                break;
            case 6:
                cout << "\nExiting program...\n";
                break;
            default:
                cout << "\nInvalid option...\n\n";
                system("pause");
                break;
        }

    } while (option != 6);
}