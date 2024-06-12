#define MAX_CH 80
#define MAX_CAT 1000
using namespace std;

typedef struct BOOK {
    string ISBN = "";
    string title = "";
    string author = "";
    int year = 0;
    bool available = false;
} BOOK;

fstream catalogue;
fstream counter;
BOOK book_array[MAX_CAT];
int book_count = 0;
int current_year = 2024;
int minimum_year = 1900;