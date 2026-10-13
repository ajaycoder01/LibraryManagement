
#include "../include/StudentManager.h"
#include "../include/BookManager.h"
#include "../include/Issue.h"
#include "../include/Book.h"

//#include "StudentManager.h"

#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstring>



//#error THIS IS MY STUDENTMANAGER.CPP
//#error Which StudentManager.h is included?
//#pragma message("StudentManager header loaded")


void StudentManager::setCurrentStudent(const Student &student)
{
    currentStudent = student;
}



void StudentManager::studentMenu()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("STUDENT MANAGEMENT");

        cout<<"1. Add Student"<<endl;
        cout<<"2. View Students"<<endl;
        cout<<"3. Search Student"<<endl;
        cout<<"4. Update Student"<<endl;
        cout<<"5. Delete Student"<<endl;
        cout<<"6. Student Statistics"<<endl;
		cout<<"7. Change Student Status"<<endl;
		cout<<"8. Back"<<endl;

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
			    studentStatistics();
			    break;
			
			case 7:
			    changeStudentStatus();
			    break;
			
			case 8:
			    break;

            default:
                cout<<"\nInvalid Choice";
                Utility::pressEnter();
        }

    }while(choice!=8);
}


int StudentManager::generateStudentID()
{
    Student student;

    int lastID = 1000;

    ifstream file("data/students.dat",ios::binary);

    if(!file)
        return 1001;

    while(file.read((char*)&student,sizeof(Student)))
    {
        lastID = student.studentId;
    }

    file.close();

    return lastID+1;
}

bool StudentManager::studentExists(int id)
{
    Student student;

    ifstream file("data/students.dat",ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&student,sizeof(Student)))
    {
        if(student.studentId==id)
        {
            file.close();

            return true;
        }
    }

    file.close();

    return false;
}

void StudentManager::addStudent()
{
    Student student;

    student.studentId = generateStudentID();

    cout<<"\nGenerated Student ID : "<<student.studentId<<endl;

    student.input();

    ofstream file("data/students.dat",ios::binary|ios::app);

    if(!file)
    {
        cout<<"\nUnable To Open File.";

        Utility::pressEnter();

        return;
    }

    file.write((char*)&student,sizeof(Student));

    file.close();

    cout<<"\nStudent Added Successfully.";

    Utility::pressEnter();
}

void StudentManager::viewStudents()
{
    Student student;

    ifstream file("data/students.dat",ios::binary);

    if(!file)
    {
        cout<<"\nNo Record Found.";

        Utility::pressEnter();

        return;
    }

    cout<<"\n============================================================================================\n";

    cout<<left
        <<setw(8)<<"ID"
        <<setw(22)<<"Name"
        <<setw(15)<<"Course"
        <<setw(15)<<"Branch"
        <<setw(10)<<"Semester"
        <<setw(15)<<"Mobile"
        <<endl;

    cout<<"============================================================================================\n";

    while(file.read((char*)&student,sizeof(Student)))
    {
        student.displayTable();
    }

    cout<<"============================================================================================\n";

    file.close();

    Utility::pressEnter();
}

void StudentManager::searchStudent()
{
    Student student;

    int choice;

    cout << "\n========== SEARCH STUDENT ==========\n";
    cout << "1. Search By ID\n";
    cout << "2. Search By Name\n";
    cout << "Enter Choice : ";
    cin >> choice;

    ifstream file("data/students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    bool found = false;

    if(choice == 1)
    {
        int id;

        cout << "\nEnter Student ID : ";
        cin >> id;

        while(file.read((char*)&student,sizeof(Student)))
        {
            if(student.studentId == id)
            {
                cout << "\n---------------------------------\n";
                student.display();
                cout << "---------------------------------\n";

                found = true;
                break;
            }
        }
    }
    else if(choice == 2)
    {
        char searchName[100];

        cin.ignore();

        cout << "\nEnter Student Name : ";
        cin.getline(searchName,100);

        while(file.read((char*)&student,sizeof(Student)))
        {
//            if(stricmp(student.name,searchName)==0)   // ? No (Case-insensitive)
//            {
//                cout << "\n---------------------------------\n";
//                student.display();
//                cout << "---------------------------------\n";
//
//                found = true;
//            }
			if(strcmp(student.name, searchName) == 0)    // ? Yes (Case-sensitive)
			{
				 cout << "\n---------------------------------\n";
			    student.display();
			     cout << "\n---------------------------------\n";
			    found = true;
			}
        }
    }
    else
    {
        cout << "\nInvalid Choice.";
    }

    file.close();

    if(!found)
        cout << "\nStudent Not Found.";

    Utility::pressEnter();
}

void StudentManager::updateStudent()
{
    int id;

    cout << "\nEnter Student ID To Update : ";
    cin >> id;

    ifstream file("data/students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    ofstream temp("data/temp.dat", ios::binary);

    Student student;

    bool found = false;

    while(file.read((char*)&student,sizeof(Student)))
    {
        if(student.studentId == id)
        {
            found = true;

            cout << "\nCurrent Details\n";
            student.display();

            cin.ignore();

            cout << "\nEnter New Name : ";
            cin.getline(student.name,100);

            cout << "Course : ";
            cin.getline(student.course,50);

            cout << "Branch : ";
            cin.getline(student.branch,50);

            cout << "Semester : ";
            cin >> student.semester;

            cin.ignore();

            cout << "Mobile : ";
            cin.getline(student.mobile,15);

            cout << "Email : ";
            cin.getline(student.email,100);
        }

        temp.write((char*)&student,sizeof(Student));
    }

    file.close();
    temp.close();

    remove("data/students.dat");
    rename("data/temp.dat","data/students.dat");

    if(found)
        cout << "\nStudent Updated Successfully.";
    else
        cout << "\nStudent Not Found.";

    Utility::pressEnter();
}

void StudentManager::deleteStudent()
{
    int id;

    cout << "\nEnter Student ID To Delete : ";
    cin >> id;

    ifstream file("data/students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    ofstream temp("data/temp.dat", ios::binary);

    Student student;

    bool found = false;

    while(file.read((char*)&student,sizeof(Student)))
    {
        if(student.studentId == id)
        {
            found = true;
            continue;
        }

        temp.write((char*)&student,sizeof(Student));
    }

    file.close();
    temp.close();

    remove("data/students.dat");
    rename("data/temp.dat","data/students.dat");

    if(found)
        cout << "\nStudent Deleted Successfully.";
    else
        cout << "\nStudent Not Found.";

    Utility::pressEnter();
}

void StudentManager::studentStatistics()
{
    Student student;

    ifstream file("data/students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    int totalStudents = 0;
    int activeStudents = 0;
    int inactiveStudents = 0;

    while(file.read((char*)&student, sizeof(Student)))
    {
        totalStudents++;

        if(student.active)
            activeStudents++;
        else
            inactiveStudents++;
    }

    file.close();

    Utility::header("STUDENT STATISTICS");

    cout << "\nTotal Students    : " << totalStudents;
    cout << "\nActive Students   : " << activeStudents;
    cout << "\nInactive Students : " << inactiveStudents;

    Utility::pressEnter();
}

void StudentManager::changeStudentStatus()
{
    int id;

    cout << "\nEnter Student ID : ";
    cin >> id;

    ifstream file("data/students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Record Found.";
        Utility::pressEnter();
        return;
    }

    ofstream temp("data/temp.dat", ios::binary);

    Student student;

    bool found = false;

    while(file.read((char*)&student,sizeof(Student)))
    {
        if(student.studentId == id)
        {
            found = true;

            cout << "\nCurrent Status : ";

            if(student.active)
                cout << "Active";
            else
                cout << "Inactive";

            cout << "\n\n";
            cout << "1. Activate Student\n";
            cout << "2. Deactivate Student\n";

            int choice;

            cout << "\nEnter Choice : ";
            cin >> choice;

            if(choice == 1)
            {
                student.active = true;
            }
            else if(choice == 2)
            {
                student.active = false;
            }
            else
            {
                cout << "\nInvalid Choice.";
            }
        }

        temp.write((char*)&student,sizeof(Student));
    }

    file.close();
    temp.close();

    remove("data/students.dat");
    rename("data/temp.dat","data/students.dat");

    if(found)
        cout << "\nStudent Status Updated Successfully.";
    else
        cout << "\nStudent Not Found.";

    Utility::pressEnter();
}



void StudentManager::studentPanel()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("STUDENT PANEL");

        cout<<"Welcome : "<<currentStudent.name<<endl;
        cout<<"Student ID : "<<currentStudent.studentId<<endl;

        cout<<"\n----------------------------\n";

        cout<<"1. View Profile"<<endl;
        cout<<"2. Search Book"<<endl;
        cout<<"3. My Issued Books"<<endl;
        cout<<"4. View Fine"<<endl;
        cout<<"5. Change Password"<<endl;
        cout<<"6. Logout"<<endl;

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            currentStudent.display();
            Utility::pressEnter();
            break;

        case 2:
        {
            BookManager bm;
            bm.searchBook();
            break;
        }

        case 3:
            myIssuedBooks();
            break;

        case 4:
            cout<<"\nYour Fine : "<<currentStudent.fine;
            Utility::pressEnter();
            break;

        case 5:
            changePassword();
            break;

        case 6:
            cout<<"\nLogout Successfully...";
            Utility::pressEnter();
            break;

        default:
            cout<<"\nInvalid Choice";
            Utility::pressEnter();
        }

    }while(choice != 6);
}


void StudentManager::changePassword()
{
    char oldPass[30];
    char newPass[30];


    cout << "\nEnter Old Password : ";
    cin >> oldPass;


    if(strcmp(currentStudent.password, oldPass) != 0)
    {
        cout << "\nWrong Old Password!";

        Utility::pressEnter();

        return;
    }



    cout << "\nEnter New Password : ";
    cin >> newPass;



    // Update Current Object

    strcpy(currentStudent.password, newPass);



ifstream file(STUDENT_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout << "\nFile Not Found";

        Utility::pressEnter();

        return;
    }



    ofstream temp("data/temp.dat", ios::binary);



    Student student;



    while(file.read((char*)&student, sizeof(Student)))
    {

        if(student.studentId == currentStudent.studentId)
        {
            strcpy(student.password, currentStudent.password);
        }


        temp.write((char*)&student, sizeof(Student));

    }



    file.close();
    temp.close();



    remove(STUDENT_FILE.c_str());

    rename("data/temp.dat", STUDENT_FILE.c_str());



    cout << "\nPassword Changed Successfully";


    Utility::pressEnter();

}

void StudentManager::myIssuedBooks()
{
    system("cls");

    Utility::header("MY ISSUED BOOKS");

    Issue issue;

    ifstream issueFile(ISSUE_FILE.c_str(), ios::binary);

    if(!issueFile)
    {
        cout<<"No Issue Record Found";
        Utility::pressEnter();
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(25)<<"Book Name"
        <<setw(20)<<"Author"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Due Date"
        <<setw(12)<<"Status"
        <<endl;

    cout<<"===================================================================================="<<endl;

    while(issueFile.read((char*)&issue, sizeof(Issue)))
    {
        if(issue.studentId == currentStudent.studentId)
        {
            Book book;

            ifstream bookFile(BOOK_FILE.c_str(), ios::binary);

            while(bookFile.read((char*)&book, sizeof(Book)))
            {
                if(book.bookId == issue.bookId)
                {
                    found = true;

                    cout<<setw(10)<<issue.issueId
                        <<setw(25)<<book.title
                        <<setw(20)<<book.author
                        <<setw(15)<<issue.issueDate
                        <<setw(15)<<issue.dueDate
                        <<setw(12)
                        <<(issue.returned ? "Returned" : "Issued")
                        <<endl;

                    break;
                }
            }

            bookFile.close();
        }
    }

    issueFile.close();

    if(!found)
    {
        cout<<"\nNo Issued Books Found.";
    }

    Utility::pressEnter();
}


