#ifndef ISSUE_H
#define ISSUE_H

#include "Constants.h"
#include <iostream>

using namespace std;


class Issue
{

public:

    int issueId;

    int studentId;

    int bookId;


    char issueDate[20];

    char dueDate[20];

    char returnDate[20];


    float fine;


    bool returned;


    Issue();


    void display();

};


#endif
