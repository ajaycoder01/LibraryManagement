#include "../include/Student.h"
#include <iomanip>  // nput/Output Manipulators header (output ko format karne ke liye).

Student::Student()
{
    studentId = 0;

    semester = 1;

    fine = 0;

    active = true;

    strcpy(password,"12345");
}

void Student::input()
{
    cin.ignore();

    do
{
    cout<<"Student Name : ";
    cin.getline(name,100);

    if(strlen(name)==0)
        cout<<"Name Cannot Be Empty.\n";

}while(strlen(name)==0);

    cout<<"Course : ";
    cin.getline(course,50);

    cout<<"Branch : ";
    cin.getline(branch,50);

do
{
    cout<<"Semester (1-8) : ";
    cin>>semester;

    if(semester<1 || semester>8)
        cout<<"Invalid Semester. Enter Between 1 To 8.\n";

}while(semester<1 || semester>8);

cin.ignore();

    cin.ignore();

do
{
    cout<<"Mobile : ";
    cin.getline(mobile,15);

    if(strlen(mobile)!=10)
    {
        cout<<"Mobile Number Must Be 10 Digits.\n";
        continue;
    }

    bool valid=true;

    for(int i=0; mobile[i]!='\0'; i++)
    {
        if(mobile[i]<'0' || mobile[i]>'9')
        {
            valid=false;
            break;
        }
    }

    if(valid)
        break;

    cout<<"Mobile Number Should Contain Digits Only.\n";

}while(true);

   do
{
    cout<<"Email : ";
    cin.getline(email,100);

    if(strchr(email,'@') && strchr(email,'.'))
        break;

    cout<<"Invalid Email Address.\n";

}while(true);
}

void Student::display()
{
    cout<<"\nStudent ID : "<<studentId<<endl;

    cout<<"Name : "<<name<<endl;

    cout<<"Course : "<<course<<endl;

    cout<<"Branch : "<<branch<<endl;

    cout<<"Semester : "<<semester<<endl;

    cout<<"Mobile : "<<mobile<<endl;

    cout<<"Email : "<<email<<endl;

    cout<<"Fine : "<<fine<<endl;

    cout<<"Status : ";

    if(active)
        cout<<"Active";
    else
        cout<<"Inactive";

    cout<<endl;
}

void Student::displayTable()
{
    cout<<left       // left ek C++ ka manipulator hai jo <iomanip> header file se aata hai. (output print hoga, usko left side align karo.")
        <<setw(8)<<studentId
        <<setw(22)<<name
        <<setw(15)<<course
        <<setw(15)<<branch
        <<setw(10)<<semester
        <<setw(15)<<mobile
        <<endl;
}
