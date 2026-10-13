#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>    // C++ ne C ke  <string.h> headers ko naye naam diye.

using namespace std;

class Student
{
public:

    int studentId;

    char name[100];

    char course[50];

    char branch[50];

    int semester;

    char mobile[15];

    char email[100];

    char password[30];

    float fine;

    bool active;

    Student();

    void input();

    void display();

    void displayTable();
};

#endif
