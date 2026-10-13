#include "../include/Library.h"
#include "../include/Login.h"
#include "../include/Admin.h"
#include "../include/StudentManager.h"

void Library::start()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("LIBRARY MANAGEMENT SYSTEM");

        cout << "1. Admin Login" << endl;
        cout << "2. Student Login" << endl;
        cout << "3. Exit" << endl;

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
        case 1:

            adminLogin();
            break;

        case 2:

            studentLogin();
            break;

        case 3:

            cout<<"\nThank You...\n";
            break;

        default:

            cout<<"\nInvalid Choice...\n";
            Utility::pressEnter();

        }

    }
    while(choice!=3);
}

void Library::adminLogin()
{
    Login login;

    if(login.adminLogin())
    {
        Admin admin;

        admin.dashboard();
    }
}


void Library::studentLogin()
{
    Login login;


    Student studentData;


    if(login.studentLogin(studentData))
    {

        StudentManager student;


        student.setCurrentStudent(studentData);


        student.studentPanel();

    }

}
