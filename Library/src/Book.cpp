#include "../include/Book.h"
#include <iomanip>

Book::Book()
{
    bookId = 0;

    price = 0;

    quantity = 0;

    available = 0;

    issued = 0;
}

void Book::input()
{
    cin.ignore();

    cout<<"Book Name : ";
    cin.getline(title,100);

    cout<<"Author : ";
    cin.getline(author,100);

    cout<<"Publisher : ";
    cin.getline(publisher,100);

    cout<<"Category : ";
    cin.getline(category,50);

    cout<<"ISBN : ";
    cin.getline(isbn,30);

    cout<<"Price : ";
    cin>>price;

    cout<<"Quantity : ";
    cin>>quantity;

    available=quantity;

    issued=0;
}

void Book::display()
{
    cout<<"\n=========================================\n";

    cout<<"Book ID       : "<<bookId<<endl;

    cout<<"Book Name     : "<<title<<endl;

    cout<<"Author        : "<<author<<endl;

    cout<<"Publisher     : "<<publisher<<endl;

    cout<<"Category      : "<<category<<endl;

    cout<<"ISBN          : "<<isbn<<endl;

    cout<<"Price         : "<<price<<endl;

    cout<<"Quantity      : "<<quantity<<endl;

    cout<<"Available     : "<<available<<endl;

    cout<<"Issued        : "<<issued<<endl;

    cout<<"=========================================\n";
}

void Book::displayTable()
{
    cout<<left
        <<setw(8)<<bookId
        <<setw(25)<<title
        <<setw(20)<<author
        <<setw(18)<<category
        <<setw(10)<<quantity
        <<setw(12)<<available
        <<setw(10)<<issued
        <<endl;
}
