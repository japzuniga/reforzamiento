#include <iostream>
#include <string>
#include "variables.h"
using namespace std;

//entradas:
int inputYear();
string inputISBN();
string inputTitle_Author(int option);
bool inputAvailability();

//CRUD: create, read, (find), update, delete
void addBooks(int amount);
void showBooks();
void show_last_x_years(int x);
int findBook();
void updateBook();
void deleteBook();

int inputYear() {
    int year;
    while (true) {
        cout << "Enter year of publication: ";
        cin >> year;
        if ((year > currentYear) || (year < minimumYear)) {
            cout << "\nERROR: Invalid input...\n\n";
            continue;
        } else {
            break;
        }
    }

    return year;
}

string inputISBN() {
    string ISBN;
    while (true) {
        cout << "Enter ISBN: ";
        cin >> ISBN;
        if ((ISBN.length() > 13) || (ISBN.length() < 10)) {
            cout << "\nERROR: Invalid input...\n\n";
            continue;
        } else {
            break;
        }
    }

    return ISBN;
}

string inputTitle_Author(int option) {
    string input;

    while (true) {
        if (option == 0) {
            cout << "Enter title: ";
        } else if (option == 1) {
            cout << "Enter author: ";
        }
        
        cin >> ws;
        getline(cin, input);
        if (input.length() > MAX_CH) {
            cout << "\nERROR: Invalid input...\n\n";   
            continue;
        } else {
            break;
        }
    }

    return input;
}

bool inputAvailability() {
    string input;
    bool available;

    while (true) {
        cout << "Is the book available? (y/n) ";
        cin >> input;
        
        if ((input == "y") || (input == "Y")) {
            available = true;
            break;
        } else if ((input == "n") || (input == "N")) {
            available = false;
            break;
        } else {
            cout << "\nInvalid input...\n\n";
            continue;
        }
    }

    return available;
}

void addBooks(int amount) {
    system("cls || clear");
    cout << "\n\t\t\tNew Book(s):\n";
    cout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < amount; i++) {
        cout << "\n\tBook " << i+1 << ":\n";
        cout << "************************";

        cout << "\n";
        catalogue[position].year = inputYear();
        catalogue[position].ISBN = inputISBN();
        catalogue[position].title = inputTitle_Author(0);
        catalogue[position].author = inputTitle_Author(1);
        catalogue[position].available = inputAvailability();

        position++;
    }

    cout << "\nBook(s) registered...\n\n";
}

void showBooks() {
    cout << "\n\t\t\tRegistered Books:\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < position; i++) {
        string availability = (catalogue[i].available) ? "Yes" : "No";

        cout << "\n\tBook " << i+1 << ":\n";
        cout << "************************";
        
        cout << "\nYear: " << catalogue[i].year;
        cout << "\nISBN: " << catalogue[i].ISBN;
        cout << "\nTitle: " << catalogue[i].title;
        cout << "\nAuthor: " << catalogue[i].author;
        cout << "\nAvailable: " << availability << "\n";
    }

    cout << "\n";
}

void show_last_x_years(int x) {
    system("cls || clear");
    int counter = 0;
    
    cout << "\n\t\tRecent Books (last " << x << " years):\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < position; i++) {
        string availability = (catalogue[i].available) ? "Yes" : "No";

        if (catalogue[i].year >= currentYear - x) {
            cout << "\n\tBook " << i+1 << ":\n";
            cout << "************************";
            cout << "\nYear: " << catalogue[i].year;
            cout << "\nISBN: " << catalogue[i].ISBN;
            cout << "\nTitle: " << catalogue[i].title;
            cout << "\nAuthor: " << catalogue[i].author;
            cout << "\nAvailable: " << catalogue[i].available << "\n";
            counter++;
        }
    }

    if (counter == 0) {
        cout << "\nNo books found...\n";
    }

    cout << "\n";
}

int findBook() {
    string tempISBN;
    int book_pos = -1;

    cout << "\nWhich book's information do you wish to update?\n";
    tempISBN = inputISBN();

    for (int i = 0; i < position; i++) {
        if (tempISBN == catalogue[i].ISBN) {
            book_pos = i;
            break;
        }
    }

    return book_pos;
}

void updateBook() {;
    int info, book_pos = -1;

    book_pos = findBook();

    if (book_pos == -1) {
        cout << "\nBook not found...\n";
        return;
    }

    else {    
        cout << "\nWhich information do you wish to update?\n";
        cout << "1. Year\n2. ISBN\n3. Title\n4. Author\n5. Availability\nEnter: ";
        cin >> info;

        cout << "\n";
        switch (info) {
            case 1:
                catalogue[book_pos].year = inputYear();
                break;
            case 2:
                catalogue[book_pos].ISBN = inputISBN();
                break;
            case 3:
                catalogue[book_pos].title = inputTitle_Author(0);
                break;
            case 4:
                catalogue[book_pos].author = inputTitle_Author(1);
                break;
            case 5:
                catalogue[book_pos].available = inputAvailability();
                break;
            default:
                cout << "\nInvalid option...";
                break;
        }

        if (info >= 1 && info <= 5) {
            cout << "\nBook information updated...\n\n";
        }
    }
}

void deleteBook() {
    int book_pos = -1;

    book_pos = findBook();

    if (book_pos == -1) {
        cout << "\nBook not found...\n\n";
    } else {
        for (int i = book_pos; i < position-1; i++) {
            catalogue[i] = catalogue[i+1];
        }

        cout << "\nBook deleted from catalogue...\n\n";
        position--;
    }
}