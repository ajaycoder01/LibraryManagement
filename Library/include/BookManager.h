#ifndef BOOKMANAGER_H       // Ye header guard hai.
#define BOOKMANAGER_H       // Agar ek header file ko galti se multiple times include kar liya:

#include "Book.h"
#include "Utility.h"
#include "Constants.h"

class BookManager
{
private:
 

    int generateBookID();
    
    bool isbnExists(const char isbn[]);

    bool bookExists(int id);

public:

    void bookMenu();

    void addBook();

    void viewBooks();

    void searchBook();

    void updateBook();

    void deleteBook();

    void searchByName();

    void searchByAuthor();

    void statistics();
    
void lowStockBooks();

};

#endif
