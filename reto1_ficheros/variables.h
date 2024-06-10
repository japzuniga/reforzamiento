#define MAX_CH 80
#define MAX_CAT 1000
using namespace std;

typedef struct BOOK {
    int year;
    string ISBN;
    string title;
    string author;
    bool available = true;
} BOOK;

fstream catalogue;
int currentYear = 2024;
int minimumYear = 1900;