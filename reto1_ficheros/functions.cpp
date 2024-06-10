#include <iostream>
#include <fstream>
#include <string>
#include "variables.h"
using namespace std;

//entradas:
int inputYear();
string inputISBN();
string inputTitle_Author(int option);
bool inputAvailability();

//little helpers:
int findBook();
BOOK readBook();

//CRUD: create, read, update, delete
void addBooks();
void showBooks();
void show_last_x_years(int x);
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

//***********************************************************************************************************

BOOK readBook(int position) {
    BOOK book;
    catalogue.open("books.txt", ios::in);
    catalogue.seekg(position, catalogue.beg);

    catalogue << book.year;
    catalogue << book.ISBN;
    catalogue << book.title;
    catalogue << book.author;
    catalogue << book.available;

    catalogue.close();
    return book;
}

int findBook() {
    BOOK book;
    string tempISBN;
    int book_pos = -1;
    catalogue.open("books.txt", ios::in);

    cout << "\nWhich book are you looking for?\n";
    tempISBN = inputISBN();

    while (catalogue.peek() != EOF) {
        book = readBook(catalogue.tellg());
        if (tempISBN == book.ISBN) {
            book_pos = catalogue.tellg();
            break;
        }
    }

    return book_pos;
}

//***********************************************************************************************************

void addBooks() {
    BOOK book;
    catalogue.open("books.txt", ios::app);

    cout << "\n";
    book.year = inputYear();
    book.ISBN = inputISBN();
    book.title = inputTitle_Author(0);
    book.author = inputTitle_Author(1);
    book.available = inputAvailability();

    catalogue.write((char*)&book, sizeof(BOOK));

    catalogue.close();
}

void showBooks() {
    BOOK book;
    int i = 0;
    catalogue.open("books.txt", ios::in);

    cout << "\n\t\t\tRegistered Books:\n";
    cout << "---------------------------------------------------------------\n";

    while (catalogue.peek() != EOF) {
        book = readBook(catalogue.tellg());
        string availability = (book.available) ? "Yes" : "No";

        cout << "\n\tBook " << i+1 << ":\n";
        cout << "************************";
        
        cout << "\nYear: " << book.year;
        cout << "\nISBN: " << book.ISBN;
        cout << "\nTitle: " << book.title;
        cout << "\nAuthor: " << book.author;
        cout << "\nAvailable: " << availability << "\n";
        i++;
    }

    cout << "\n";
    catalogue.close();
}

void show_last_x_years(int x) {
    BOOK tempCatalogue[MAX_CAT];
    int i = 0, counter = 0;

    catalogue.open("books.txt", ios::in);

    cout << "\n\t\t\tRecent Books (last " << x << " years):\n";
    cout << "---------------------------------------------------------------\n";

    while (catalogue.peek() != EOF) {
        tempCatalogue[i] = readBook(catalogue.tellg());
        if (tempCatalogue[i].year >= currentYear - x) {
            string availability = (tempCatalogue[i].available) ? "Yes" : "No";

            cout << "\n\tBook " << i+1 << ":\n";
            cout << "************************";
            cout << "\nYear: " << tempCatalogue[i].year;
            cout << "\nISBN: " << tempCatalogue[i].ISBN;
            cout << "\nTitle: " << tempCatalogue[i].title;
            cout << "\nAuthor: " << tempCatalogue[i].author;
            cout << "\nAvailable: " << tempCatalogue[i].available << "\n";
            counter++;
        }

        i++;
    }

    if (counter == 0) {
        cout << "\nNo books found...\n";
    }

    cout << "\n";
    catalogue.close();
}

//***********************************************************************************************************

void updateBook() {
    BOOK book;
    int info, book_pos;

    book_pos = findBook();

    if (book_pos == -1) {
        cout << "\nBook not found...\n";
        return;
    }

    else {
        catalogue.open("books.txt", ios::in | ios::out);
        catalogue.seekg(book_pos, catalogue.beg);

        catalogue << book.year;
        catalogue << book.ISBN;
        catalogue << book.title;
        catalogue << book.author;
        catalogue << book.available;

        cout << "\nWhich information do you wish to update?\n";
        cout << "1. Year\n2. ISBN\n3. Title\n4. Author\n5. Availability\nEnter: ";
        cin >> info;

        cout << "\n";
        switch (info) {
            case 1:
                book.year = inputYear();
                break;
            case 2:
                book.ISBN = inputISBN();
                break;
            case 3:
                book.title = inputTitle_Author(0);
                break;
            case 4:
                book.author = inputTitle_Author(1);
                break;
            case 5:
                book.available = inputAvailability();
                break;
            default:
                cout << "\nInvalid option...";
                break;
        }

        if (info >= 1 && info <= 5) {
            catalogue.seekg(book_pos, catalogue.beg);
            catalogue.write((char*)&book, sizeof(BOOK));
            cout << "\nBook information updated...\n\n";
        }
    }
}

/*void deleteBook() {
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
}*/