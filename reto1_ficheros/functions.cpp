#include <iostream>
#include <fstream>
#include <string>
#include "variables.h"
using namespace std;

//guess:
void menu();

//entradas:
int checkISBN(string ISBN);
string input_ISBN();
string input_Title_Author(int option);
int input_Year();
bool input_Availability();

//little helpers:
bool write_to_file();
bool read_from_file();
int find_book();

//CRUD: create, read, update, delete
void add_books(int amount);
void show_books();
void show_last_x_years(int x);
void update_book();
void delete_book();

//***********************************************************************************************************

void menu() {
    int option = 0;

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
                system("cls || clear");
                add_books(amount);                
                system("pause");
                break;
            case 2:
                system("cls || clear");
                show_books();
                system("pause");
                break;
            case 3:
                int x;
                cout << "\nHow recent do you wish the books shown to be? (in years) ";
                cin >> x;                
                system("cls || clear");
                show_last_x_years(x);
                system("pause");
                break;
            case 4:
                system("cls || clear");
                update_book();
                system("pause");
                break;
            case 5:
                system("cls || clear");
                delete_book();
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

//***********************************************************************************************************

int checkISBN(string ISBN) {
    bool check = read_from_file();

    if (check && book_count > 0) {
        for (int i = 0; i < book_count; i++) {
            if (ISBN == book_array[i].ISBN) {
                return 0;
                break;
            }
        }
    }

    else if (book_count == 0) return -1;
    else return -1;

    return 1;
}

string input_ISBN() {
    string ISBN = "";
    
    while (true) {
        cout << "Enter ISBN: ";
        cin >> ISBN;

        if ((ISBN.length() > 13) || (ISBN.length() < 10)) {
            cout << "\nERROR: Invalid input...\n\n";
            continue;
        } else break;
    }

    return ISBN;
}

string input_Title_Author(int option) {
    string input = "";

    while (true) {
        if (option == 0) cout << "Enter title: ";
        else if (option == 1) cout << "Enter author: ";
        
        cin >> ws;
        getline(cin, input);

        if (input.length() > MAX_CH) {
            cout << "\nERROR: Invalid input...\n\n";
            continue;
        } else break;
    }

    return input;
}

int input_Year() {
    int year = 0;

    while (true) {
        cout << "Enter year of publication: ";
        cin >> year;

        if ((year > current_year) || (year < minimum_year)) {
            cout << "\nERROR: Invalid input...\n\n";
            continue;
        } else break;
    }

    return year;
}

bool input_Availability() {
    string input = "";
    bool available = false;

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

bool read_from_file() {
    int i = 0;
    catalogue.open("books.txt", ios::in);
    counter.open("length.txt", ios::trunc | ios::out);

    if (catalogue.is_open()) {
        while (catalogue >> book_array[i].ISBN >> ws && getline(catalogue, book_array[i].title)
               && catalogue >> ws && getline(catalogue, book_array[i].author)
               && catalogue >> book_array[i].year >> book_array[i].available) { i++; }
    }
    
    else return false;

    book_count = i;
    counter << book_count;

    counter.close();
    catalogue.close();
    return true;
}

bool write_to_file() {
    int x = 0;
    catalogue.open("books.txt", ios::trunc | ios::out);
    counter.open("length.txt", ios::trunc | ios::out | ios::in);

    if (catalogue.is_open() && counter.is_open()) {
        for (int i = 0; i < book_count; i++) {
            catalogue << book_array[i].ISBN << "\n";
            catalogue << book_array[i].title << "\n";
            catalogue << book_array[i].author << "\n";
            catalogue << book_array[i].year << "\n";
            catalogue << book_array[i].available << "\n";
            x++;
        }
    } else return false;

    book_count = x;
    counter << book_count;
    
    counter.close();
    catalogue.close();
    return true;
}

int find_book() {
    string tempISBN = "";
    int book_position = -1;
    bool check = read_from_file();

    if (check && book_count > 0) {
        while (true) {
            cout << "\nWhich book are you looking for?\n";
            tempISBN = input_ISBN();

            for (int i = 0; i < book_count; i++) {
                if (tempISBN == book_array[i].ISBN) {
                    book_position = i;
                    break;
                }
            }

            if (book_position == -1) {
                cout << "\nBook not found...\n";
                continue;
            } else break;
        }
    }

    else if (book_count == 0) cout << "\nNo books are currently registered...\n\n";
    else cout << "\nERROR: file could not be opened...\n\n";

    return book_position;
}

//***********************************************************************************************************

void add_books(int amount_to_add) {
    bool check = read_from_file();

    if (!check) cout << "\nERROR: file could not be opened...\n\n";
    
    else {
        cout << "\n\t\t\tNew Book(s):\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < amount_to_add; i++) {
            cout << "\n\tBook " << i+1 << ":\n";
            cout << "************************";

            cout << "\n";

            while (true) {
                book_array[book_count].ISBN = input_ISBN();
                if ((checkISBN(book_array[book_count].ISBN) == 0)) {
                    cout << "\nERROR: ISBN already registered...\n\n";
                    continue;
                } else if ((checkISBN(book_array[book_count].ISBN) < 0)) {
                    cout << "\nFILE ERROR...\n\n";
                    continue;
                } else break;
            }

            book_array[book_count].title = input_Title_Author(0);
            book_array[book_count].author = input_Title_Author(1);
            book_array[book_count].year = input_Year();
            book_array[book_count].available = input_Availability();
            book_count++;
        }

        bool save = write_to_file();
        if (save) cout << "\nBook(s) registered...\n\n";
        else cout << "\nERROR: books could not be saved to file...\n\n";
    }
}

void show_books() {
    bool check = read_from_file();

    if (check && book_count > 0) {
        cout << "\n\t\t\tRegistered Books:\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < book_count; i++) {
            string availability = (book_array[i].available) ? "Yes" : "No";

            cout << "\n\tBook " << i+1 << ":\n";
            cout << "************************";
            cout << "\nISBN: " << book_array[i].ISBN;
            cout << "\nTitle: " << book_array[i].title;
            cout << "\nAuthor: " << book_array[i].author;
            cout << "\nYear: " << book_array[i].year;
            cout << "\nAvailable: " << availability << "\n";
        }

        cout << "\n";
    }

    else if (book_count == 0) cout << "\nNo books are currently registered...\n\n";
    else cout << "\nERROR: file could not be opened...\n\n";
}

void show_last_x_years(int x) {
    bool check = read_from_file();
    int counter = 0;

    if (check && book_count > 0) {
        cout << "\n\t\t\tRecent Books (last " << x << " years):\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < book_count; i++) {
            if (book_array[i].year >= current_year - x) {
                string availability = (book_array[i].available) ? "Yes" : "No";

                cout << "\n\tBook " << i+1 << ":\n";
                cout << "************************";
                cout << "\nISBN: " << book_array[i].ISBN;
                cout << "\nTitle: " << book_array[i].title;
                cout << "\nAuthor: " << book_array[i].author;
                cout << "\nYear: " << book_array[i].year;
                cout << "\nAvailable: " << book_array[i].available << "\n";
                counter++;
            }

        }

        if (counter == 0) cout << "\nNo books found...\n";
        else if (counter > 0) cout << "\n";
    }

    else if (book_count == 0) cout << "\nNo books are currently registered...\n\n";
    else cout << "\nERROR: file could not be opened...\n\n";
}

//***********************************************************************************************************

void update_book() {
    int info = 0, book_position = find_book();

    if (book_position == -1) cout << "\nERROR: Book not found...\n\n";

    else {
        cout << "\nWhich information do you wish to update?\n";
        cout << "1. ISBN\n2. Title\n3. Author\n4. Year\n5. Availability\nEnter: ";
        cin >> info;

        cout << "\n";
        switch (info) {
            case 1:
                book_array[book_position].ISBN = input_ISBN();
                break;
            case 2:
                book_array[book_position].title = input_Title_Author(0);
                break;
            case 3:
                book_array[book_position].author = input_Title_Author(1);
                break;
            case 4:
                book_array[book_position].year = input_Year();
                break;
            case 5:
                book_array[book_position].available = input_Availability();
                break;
            default:
                cout << "\nInvalid option...";
                break;
        }

        if (info >= 1 && info <= 5) {
            bool save = write_to_file();
            if (save) cout << "\nBook information updated...\n\n";
            else cout << "\nERROR: file could not be opened...\n\n";
        }
    }
}

void delete_book() {
    BOOK emptyBook;
    int book_position = -1;
    book_position = find_book();

    if (book_position == -1) cout << "\nBook not found...\n\n";

    else {
        for (int i = book_position; i < book_count-1; i++) {
            book_array[i] = book_array[i+1];
        }

        book_array[book_count-1] = emptyBook;
        book_count--;
        bool save = write_to_file();
        
        if (save) cout << "\nBook deleted from catalogue...\n\n";
        else cout << "\nERROR: file could not be opened...\n\n";
    }
}