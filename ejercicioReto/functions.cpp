#include <iostream>
#include <string>
#include "variables.h"
using namespace std;

//entradas:
int checkYear();
string checkISBN();
string title_author(int option);
bool checkAvailable();

//CRUD: create, read, update, delete
void addBooks(int amount);
void showBooks();
void show_last_x_years(int x);
void updateBook();
void deleteBook();

int checkYear() {
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

string checkISBN() {
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

string title_author(int option) {
    string input;

    while (true) {
        if (option == 1) {
            cout << "Enter title: ";
        } else if (option == 2) {
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

bool checkAvailable() {
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
        catalogue[position].year = checkYear();
        catalogue[position].ISBN = checkISBN();
        catalogue[position].title = title_author(1);
        catalogue[position].author = title_author(2);
        catalogue[position].available = checkAvailable();

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
    
    cout << "\n\t\t\tRecent Books (last " << x << " years):\n";
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

void updateBook() {;
    string tempISBN, available;
    int book_pos, info;
    bool found = false;

    cout << "\nWhich book's information do you wish to update?\n";
    tempISBN = checkISBN();

    for (int i = 0; i < position; i++) {
        if (tempISBN == catalogue[i].ISBN) {
            book_pos = i;
            found = true;
            break;
        }
    }

    if (found == false) {
        cout << "\nBook not found...\n";
        return;
    }

    else if (found == true) {    
        cout << "\nWhich information do you wish to update?\n";
        cout << "1. Year\n2. ISBN\n3. Title\n4. Author\n5. Availability\nEnter: ";
        cin >> info;

        cout << "\n";
        switch (info) {
            case 1:
                catalogue[book_pos].year = checkYear();
                break;
            case 2:
                catalogue[book_pos].ISBN = checkISBN();
                break;
            case 3:
                catalogue[book_pos].title = title_author(1);
                break;
            case 4:
                catalogue[book_pos].author = title_author(2);
                break;
            case 5:
                catalogue[book_pos].available = checkAvailable();
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
    string tempISBN;
    int book_pos = -1;

    cout << "\nWhich book do you want to delete from the catalogue?\n";
    tempISBN = checkISBN();

    for (int i = 0; i < position; i++) {
        if (tempISBN == catalogue[i].ISBN) {
            book_pos = i;
            break;
        }
    }

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