#include "../include/BookManager.h"
#include <fstream>
#include <cstdio> // C language ke file handling aur input/output functions ko C++ me use karne ke liye hota hai.(remove(),rename(),fopen(),fclose())
#include <cstring>
#include <iomanip>

void BookManager::bookMenu()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("BOOK MANAGEMENT");

       cout<<"1. Add Book"<<endl;
		cout<<"2. View Books"<<endl;
		cout<<"3. Search By ID"<<endl;
		cout<<"4. Update Book"<<endl;
		cout<<"5. Delete Book"<<endl;
		cout<<"6. Search By Name"<<endl;
		cout<<"7. Search By Author"<<endl;
		cout<<"8. Statistics"<<endl;
		cout<<"9. Low Stock Books"<<endl;
		cout<<"10. Back"<<endl;
        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

           case 6:
			    searchByName();
			    break;
			
			case 7:
			    searchByAuthor();
			    break;
			
			case 8:

			    statistics();
			
			    break;
			case 9:

			    lowStockBooks();
			
			    break;
			
			case 10:
			
			    break;
            default:
                cout<<"\nInvalid Choice";
                Utility::pressEnter();
        }

    }while(choice!=10);
}

void BookManager::addBook()
{
    Book book;

    book.bookId = generateBookID();

    cout<<"\nGenerated Book ID : "<<book.bookId<<endl;

    book.input();

    if(isbnExists(book.isbn))
    {
        cout<<"\nISBN Already Exists.";

        Utility::pressEnter();

        return;
    }

    ofstream file("data/books.dat",ios::binary|ios::app);

    if(!file)
    {
        cout<<"\nUnable To Open File.";

        Utility::pressEnter();

        return;
    }

    file.write((char*)&book,sizeof(Book));

    file.close();

    cout<<"\nBook Added Successfully.";

    Utility::pressEnter();
}

void BookManager::viewBooks()
{
    Book book;

    ifstream file("data/books.dat", ios::binary);

    if(!file)
    {
        cout<<"\nNo Record Found.";

        Utility::pressEnter();
        return;
    }

    cout<<"\n============================================================================================================\n";

    cout<<left
        <<setw(8)<<"ID"
        <<setw(25)<<"Book Name"
        <<setw(20)<<"Author"
        <<setw(18)<<"Category"
        <<setw(10)<<"Qty"
        <<setw(12)<<"Available"
        <<setw(10)<<"Issued"
        <<endl;

    cout<<"============================================================================================================\n";

    while(file.read((char*)&book,sizeof(Book)))
    {
        book.displayTable();
    }

    cout<<"============================================================================================================\n";

    file.close();

    Utility::pressEnter();
}

void BookManager::searchBook()
{
    int id;

    bool found = false;

    Book book;

    cout << "\nEnter Book ID : ";
    cin >> id;

    ifstream file("data/books.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";

        Utility::pressEnter();

        return;
    }

    while(file.read((char*)&book, sizeof(Book)))
    {
        if(book.bookId == id)
        {
            cout << "\nBook Found Successfully.\n";

            book.display();

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nBook Not Found.";
    }

    Utility::pressEnter();
}

void BookManager::updateBook()
{
    int id;

    bool found = false;

    Book book;

    cout << "\nEnter Book ID To Update : ";
    cin >> id;

    ifstream file("data/books.dat", ios::binary);

    ofstream temp("data/temp.dat", ios::binary);

    if(!file || !temp)
    {
        cout << "\nFile Opening Error.";

        Utility::pressEnter();
        return;
    }

    while(file.read((char*)&book, sizeof(Book)))
    {
        if(book.bookId == id)
        {
            found = true;

            cout << "\nEnter New Book Details\n";

            book.input();

            temp.write((char*)&book, sizeof(Book));
        }
        else
        {
            temp.write((char*)&book, sizeof(Book));
        }
    }

    file.close();
    temp.close();

    remove("data/books.dat");
    rename("data/temp.dat", "data/books.dat");

    if(found)
        cout << "\nBook Updated Successfully.";
    else
        cout << "\nBook Not Found.";

    Utility::pressEnter();
}

void BookManager::deleteBook()
{
    int id;

    char choice;

    bool found = false;

    Book book;

    cout << "\nEnter Book ID To Delete : ";
    cin >> id;

    ifstream file("data/books.dat", ios::binary);

    ofstream temp("data/temp.dat", ios::binary);

    if(!file || !temp)
    {
        cout << "\nFile Opening Error.";

        Utility::pressEnter();

        return;
    }

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(book.bookId==id)
        {
            found = true;

            cout << "\nBook Found\n";

            book.display();

            cout << "\nDelete This Book? (Y/N) : ";
            cin >> choice;

            if(choice=='Y' || choice=='y')
            {
                cout << "\nBook Deleted Successfully.\n";
            }
            else
            {
                temp.write((char*)&book,sizeof(Book));

                cout << "\nDelete Cancelled.\n";
            }
        }
        else
        {
            temp.write((char*)&book,sizeof(Book));
        }
    }

    file.close();
    temp.close();

    remove("data/books.dat");
    rename("data/temp.dat","data/books.dat");

    if(!found)
    {
        cout << "\nBook Not Found.";
    }

    Utility::pressEnter();
}

bool BookManager::bookExists(int id)
{
    Book book;

    ifstream file("data/books.dat", ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&book, sizeof(Book)))
    {
        if(book.bookId == id)
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

int BookManager::generateBookID()
{
    Book book;

    int lastID = 1000;

    ifstream file("data/books.dat",ios::binary);

    if(!file)
        return 1001;

    while(file.read((char*)&book,sizeof(Book)))
    {
        lastID = book.bookId;
    }

    file.close();

    return lastID+1;
}

bool BookManager::isbnExists(const char isbn[])
{
    Book book;

    ifstream file("data/books.dat",ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(strcmp(book.isbn,isbn)==0)
        {
            file.close();

            return true;
        }
    }

    file.close();

    return false;
}

void BookManager::searchByAuthor()
{
    char author[100];

    Book book;

    bool found=false;

    cin.ignore();

    cout<<"\nEnter Author Name : ";

    cin.getline(author,100);

    ifstream file("data/books.dat",ios::binary);

    if(!file)
    {
        cout<<"\nNo Record Found.";

        Utility::pressEnter();

        return;
    }

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(strcmp(book.author,author)==0)
        {
            book.display();

            found=true;
        }
    }

    file.close();

    if(!found)
        cout<<"\nAuthor Not Found.";

    Utility::pressEnter();
}



void BookManager::searchByName()
{
    char name[100];

    Book book;

    bool found = false;

    cin.ignore();

    cout << "\nEnter Book Name : ";
    cin.getline(name,100);

    ifstream file("data/books.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(strcmp(book.title,name)==0)
        {
            book.display();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nBook Not Found.";

    Utility::pressEnter();
}


void BookManager::statistics()
{
    Book book;

    int totalBooks = 0;
    int totalQuantity = 0;
    int totalAvailable = 0;
    int totalIssued = 0;

    ifstream file("data/books.dat", ios::binary);

    if(!file)
    {
        cout<<"\nNo Record Found.";

        Utility::pressEnter();

        return;
    }

    while(file.read((char*)&book,sizeof(Book)))
    {
        totalBooks++;

        totalQuantity += book.quantity;

        totalAvailable += book.available;

        totalIssued += book.issued;
    }

    file.close();

    Utility::header("BOOK STATISTICS");

    cout<<"Total Books        : "<<totalBooks<<endl;

    cout<<"Total Quantity     : "<<totalQuantity<<endl;

    cout<<"Available Books    : "<<totalAvailable<<endl;

    cout<<"Issued Books       : "<<totalIssued<<endl;

    Utility::pressEnter();
}

void BookManager::lowStockBooks()
{
    Book book;

    bool found=false;

    ifstream file("data/books.dat",ios::binary);

    if(!file)
    {
        cout<<"\nNo Record Found.";

        Utility::pressEnter();

        return;
    }

    Utility::header("LOW STOCK BOOKS");

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(book.available<=2)
        {
            book.display();

            found=true;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Low Stock Books.";
    }

    Utility::pressEnter();
}
