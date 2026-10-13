#include "../include/Fine.h"
#include <cstring>


Fine::Fine()
{

    fineId = 0;

    issueId = 0;

    studentId = 0;

    amount = 0;


    strcpy(date,"");

}


void Fine::display()
{

    cout<<"Fine ID : "<<fineId<<endl;

    cout<<"Issue ID : "<<issueId<<endl;

    cout<<"Student ID : "<<studentId<<endl;

    cout<<"Amount : "<<amount<<endl;

    cout<<"Date : "<<date<<endl;

}
