#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include "Utility.h"
#include "Constants.h"
//
//#error THIS IS MY STUDENTMANAGER.H


class StudentManager
{
private:

    int generateStudentID();

    bool studentExists(int id);
    
    Student currentStudent;

public:

    void studentMenu();
    
    void studentPanel();

    void addStudent();

    void viewStudents();

    void searchStudent();

    void updateStudent();

    void deleteStudent();
    
    void studentStatistics();
    
    void changeStudentStatus();
    
     
     void changePassword();
     
void setCurrentStudent(const Student &student);     

void studentDashboard();
void myIssuedBooks();
void myFine();
void myProfile();
void changeStudentPassword();

};











#endif
