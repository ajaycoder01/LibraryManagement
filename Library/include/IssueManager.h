#ifndef ISSUEMANAGER_H
#define ISSUEMANAGER_H

#include "Issue.h"
#include "BookManager.h"
#include "StudentManager.h"
#include "Utility.h"
#include "Constants.h"
#include "Fine.h"

using namespace std;


class IssueManager
{

private:

 int generateIssueID();

    bool issueExists(int id);

    bool bookAlreadyIssued(int bookId, int studentId);

    bool studentExists(int id);

    bool bookExists(int id);

    void updateBookQuantity(int id);
    void updateBookAfterReturn(int id);
    
    int calculateLateDays();
    
    void updateIssueFine(int issueId, float fine);
    
    void calculateDueDate(char dueDate[]);
int calculateLateDays(char dueDate[]);

void saveFine(Issue issue);

void updateStudentFine(int studentId, float amount);

void clearStudentFine(int studentId);

void fineMenu();

void viewFineRecords();

void searchStudentFine();

void payFine();

bool canIssueMoreBooks(int studentId);

bool bookAvailable(int bookId);

bool isStudentActive(int studentId);

bool hasPendingFine(int studentId);


public:

    void issueMenu();


    // Issue Book
    void issueBook();


    // Return Book
    void returnBook();


    // View Records
    void viewIssuedBooks();


    // Search
    void searchIssue();


    // Fine
    void calculateFine();


    // Reports
    void issueStatistics();
    
    
    void searchByIssueID();
void searchByStudentID();
void searchByBookID();
void pendingIssues();
void returnedIssues();


void reportsMenu();

void totalBooksReport();
void totalStudentsReport();
void totalIssuedBooksReport();
void totalReturnedBooksReport();
void totalFineReport();
void mostIssuedBooksReport();
void overdueBooksReport();



};

#endif
