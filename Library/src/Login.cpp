#include "../include/Login.h"
//#include "../include/Student.h"
#include <fstream>
using namespace std;

bool Login::adminLogin()
{
    string username;
    string password;

    int attempts = 3;

    while(attempts > 0)
    {
        system("cls");

        Utility::header("ADMIN LOGIN");

        cout << "Username : ";
        cin >> username;

        cout << "Password : ";
        cin >> password;

        if(username == ADMIN_USERNAME &&
           password == ADMIN_PASSWORD)
        {
            cout << "\nLogin Successful...\n";

            Utility::pressEnter();

            return true;
        }

        attempts--;

        cout << "\nInvalid Username or Password.\n";
        cout << "Remaining Attempts : " << attempts << endl;

        Utility::pressEnter();
    }

    cout << "\nToo Many Failed Attempts.\n";

    Utility::pressEnter();

    return false;
}

bool Login::studentLogin(Student &student)
{
    int id;
    char pass[30];


    system("cls");

    Utility::header("STUDENT LOGIN");


    cout << "Student ID : ";
    cin >> id;


    cout << "Password : ";
    cin >> pass;



	ifstream file(STUDENT_FILE.c_str(), ios::binary);   //(ifstream)File read karne ke liye object. 
													// C-style string , Binary mode me file open karega.

    if(!file)
    {
        cout << "\nStudent Data File Not Found!";
        
        Utility::pressEnter();

        return false;
    }



    Student temp;

 // File me jitne bhi students hain unko ek-ek karke read karo.
 // Student object ka address binary format me. (char*)&temp   // pura object ek bar me read ho jaye
 // sizeof(Student)   .... Ek student object ka size jitne bytes ka hai utna read karo.
 
    while(file.read((char*)&temp, sizeof(Student)))  
    {

        // Check ID and Password

        if(temp.studentId == id &&
           strcmp(temp.password, pass) == 0)
        {


            // Check Active Status

            if(temp.active == false)
            {
                cout << "\nYour Account is Inactive!";
                
                Utility::pressEnter();

                file.close();

                return false;
            }
            
   student = temp;  // Jo student login hua hai uski sari details caller object me copy kar di jaati hain.


            cout << "\nLogin Successful...";
            cout << "\nWelcome : " << temp.name << endl;


            file.close();


            Utility::pressEnter();


            return true;

        }

    }



    file.close();


    cout << "\nInvalid Student ID or Password!";


    Utility::pressEnter();


    return false;
}
