#ifndef BOOK_H
#define BOOK_H

#include "Constants.h"


class Book
{
public:
    int bookId;

    char title[100];
    char author[100];
    char publisher[100];
    char category[50];
    char isbn[20];

    float price;

    int quantity;
    int available;
    int issued;

    Book();

    void input();

    void updateInput();

    void display();

    void displayTable();
};

#endif
