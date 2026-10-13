#include "../include/Admin.h"
#include "../include/Book.h"
#include "../include/BookManager.h"
#include "../include/StudentManager.h"
#include "../include/IssueManager.h"

void Admin::dashboard()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("ADMIN DASHBOARD");

       cout << "1. Book Management" << endl;
		cout << "2. Student Management" << endl;
		cout << "3. Issue Management" << endl;
		cout << "4. Reports" << endl;
		cout << "5. Change Password" << endl;
		cout << "6. Logout" << endl;

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
{
case 1:
{
    BookManager manager;
    manager.bookMenu();
    break;
}

case 2:
{
    StudentManager manager;
    manager.studentMenu();
    break;
}

case 3:
{
    IssueManager im;
    im.issueMenu();
    break;
}

case 4:
{
    IssueManager im;
    im.reportsMenu();
    break;
}

case 5:
{
    cout << "\nChange Password Feature Coming Soon...";
    Utility::pressEnter();
    break;
}

case 6:
{
    cout << "\nLogging Out...\n";
    Utility::pressEnter();
    break;
}

default:
{
    cout << "\nInvalid Choice.\n";
    Utility::pressEnter();
}
}

    }
    while(choice!=6);
}
