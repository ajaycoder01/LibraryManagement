#include "../include/Issue.h"
#include <cstring>
//#include <string.h>

#include <iostream>

using namespace std;


Issue::Issue()
{
    issueId = 0;

    studentId = 0;

    bookId = 0;


    strcpy(issueDate,"");

    strcpy(dueDate,"");

    strcpy(returnDate,"");


    fine = 0;


    returned = false;
}



void Issue::display()
{

    cout<<"\nIssue ID : "<<issueId;

    cout<<"\nStudent ID : "<<studentId;

    cout<<"\nBook ID : "<<bookId;

    cout<<"\nIssue Date : "<<issueDate;

    cout<<"\nDue Date : "<<dueDate;


    if(returned)
        cout<<"\nStatus : Returned";
    else
        cout<<"\nStatus : Issued";


    cout<<endl;

}
