#include "../include/IssueManager.h"
#include "../include/Utility.h"
//#include "../include/IssueManager.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;



int IssueManager::generateIssueID()
{
    Issue issue;

    int id = 1000;


    ifstream file(ISSUE_FILE.c_str(), ios::binary);


    if(!file)
        return 1001;



    while(file.read((char*)&issue, sizeof(Issue)))
    {
        id = issue.issueId;
    }


    file.close();


    return id + 1;
}




void IssueManager::issueMenu()
{
    int choice;


    do
    {
        system("cls");


        Utility::header("ISSUE MANAGEMENT");


        cout<<"1. Issue Book"<<endl;
        cout<<"2. Return Book"<<endl;
        cout<<"3. View Issued Books"<<endl;
        cout<<"4. Search Issue"<<endl;
        cout<<"5. Fine Management"<<endl;
        cout<<"6. Back"<<endl;


        cout<<"\nEnter choice : ";
        cin>>choice;



        switch(choice)
        {

        case 1:
            issueBook();
            break;


        case 2:
            returnBook();
            break;


        case 3:
            viewIssuedBooks();
            break;


        case 4:
            searchIssue();
            break;


        case 5:
            fineMenu();
            break;


        case 6:
            break;


        default:
            cout<<"Invalid Choice";
        }


        system("pause");


    }while(choice!=6);

}






void IssueManager::viewIssuedBooks()
{

    system("cls");


    Utility::header("ISSUED BOOK RECORDS");


    Issue issue;


    ifstream file(ISSUE_FILE.c_str(), ios::binary);



    if(!file)
    {
        cout<<"No Issue Record Found"<<endl;
        return;
    }



    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Issue Date"
        <<setw(12)<<"Status"
        <<endl;



    cout<<"------------------------------------------------"<<endl;



    while(file.read((char*)&issue,sizeof(Issue)))
    {

        cout<<setw(10)<<issue.issueId
            <<setw(12)<<issue.studentId
            <<setw(10)<<issue.bookId
            <<setw(15)<<issue.issueDate
            <<setw(12)
            <<(issue.returned ? "Returned":"Issued")
            <<endl;

    }



    file.close();

}


void IssueManager::issueBook()
{

    system("cls");

    Utility::header("ISSUE BOOK");


    Issue issue;


    cout<<"Enter Student ID : ";
    cin>>issue.studentId;


    cout<<"Enter Book ID : ";
    cin>>issue.bookId;

		if(!studentExists(issue.studentId))
		{
		    cout<<"Student Not Found";
		    return;
		}
		
		if(!isStudentActive(issue.studentId))
		{
		    cout<<"\nStudent Account Is Inactive";
		    return;
		}
		
		if(hasPendingFine(issue.studentId))
		{
		    cout<<"\nStudent Has Pending Fine.";
		    cout<<"\nPlease Clear The Fine First.";
		    return;
		}
		
		if(!bookExists(issue.bookId))
		{
		    cout<<"Book Not Found";
		    return;
		}
		
		if(!bookAvailable(issue.bookId))
		{
		    cout<<"\nBook Is Currently Not Available";
		    return;
		}
				
		if(bookAlreadyIssued(issue.bookId, issue.studentId))
		{
		    cout<<"Book Already Issued To This Student";
		    return;
		}
		
		if(!canIssueMoreBooks(issue.studentId))
		{
		    cout<<"\nStudent Has Already Issued Maximum "
		        <<MAX_BOOK_ISSUE
		        <<" Books.";
		
		    return;
		}


    issue.issueId = generateIssueID();


    time_t now = time(0);

    tm *ltm = localtime(&now);



    sprintf(issue.issueDate,
            "%02d/%02d/%d",
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year);


//	strcpy(issue.dueDate, "After 7 Days");
    calculateDueDate(issue.dueDate);


    strcpy(issue.returnDate, "");


    issue.fine = 0;


    issue.returned = false;



    ofstream file(ISSUE_FILE.c_str(), ios::binary | ios::app);



    if(!file)
    {
        cout<<"File Error";
        return;
    }



    file.write((char*)&issue,sizeof(Issue));


    file.close();

updateBookQuantity(issue.bookId);


    cout<<"\nBook Issued Successfully";
    cout<<"\nIssue ID : "<<issue.issueId;

}


void IssueManager::returnBook()
{

    system("cls");

    Utility::header("RETURN BOOK");


    int id;


    cout<<"Enter Issue ID : ";
    cin>>id;



    Issue issue;


    fstream file(ISSUE_FILE.c_str(), ios::in | ios::out | ios::binary);



    bool found = false;



    while(file.read((char*)&issue,sizeof(Issue)))
    {

        if(issue.issueId == id)
        {

            found = true;


            if(issue.returned)
            {
                cout<<"Book Already Returned";
                file.close();
                return;
            }



            issue.returned = true;
            
           int lateDays = calculateLateDays(issue.dueDate);


			issue.fine = lateDays * FINE_PER_DAY;
			
			if(issue.fine > 0)
				{
				    saveFine(issue);
				     updateStudentFine(issue.studentId, issue.fine);
				}



            time_t now = time(0);

            tm *ltm = localtime(&now);



            sprintf(issue.returnDate,
                    "%02d/%02d/%d",
                    ltm->tm_mday,
                    1 + ltm->tm_mon,
                    1900 + ltm->tm_year);



            file.seekp(-sizeof(Issue), ios::cur);


            file.write((char*)&issue,sizeof(Issue));



            updateBookAfterReturn(issue.bookId);



            cout<<"\nBook Returned Successfully";


            break;

        }

    }



    file.close();



    if(!found)
    {
        cout<<"Issue Record Not Found";
    }

}


void IssueManager::searchIssue()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("SEARCH ISSUE");

        cout<<"1. Search By Issue ID"<<endl;
        cout<<"2. Search By Student ID"<<endl;
        cout<<"3. Search By Book ID"<<endl;
        cout<<"4. Pending Issues"<<endl;
        cout<<"5. Returned Issues"<<endl;
        cout<<"6. Back"<<endl;

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            searchByIssueID();
            break;

        case 2:
            searchByStudentID();
            break;

        case 3:
            searchByBookID();
            break;

        case 4:
            pendingIssues();
            break;

        case 5:
            returnedIssues();
            break;

        case 6:
            break;

        default:
            cout<<"Invalid Choice";
        }

        if(choice != 6)
            system("pause");

    }while(choice != 6);
}


void IssueManager::calculateFine()
{

    system("cls");


    Utility::header("FINE MANAGEMENT");


    Issue issue;


    ifstream file(ISSUE_FILE.c_str(), ios::binary);


    float totalFine = 0;


    while(file.read((char*)&issue,sizeof(Issue)))
    {

        if(issue.fine > 0)
        {

            cout<<"Issue ID : "<<issue.issueId<<endl;

            cout<<"Student ID : "<<issue.studentId<<endl;

            cout<<"Fine : "<<issue.fine<<endl;

            cout<<"---------------------"<<endl;


            totalFine += issue.fine;

        }

    }


    file.close();


    cout<<"\nTotal Fine Collection : "<<totalFine<<endl;
    
    
//    return 0;

}


void IssueManager::issueStatistics()
{
    cout<<"Issue Statistics Coming Soon"<<endl;
}


bool IssueManager::studentExists(int id)
{

    Student student;


    ifstream file(STUDENT_FILE.c_str(), ios::binary);


    while(file.read((char*)&student,sizeof(Student)))
    {

        if(student.studentId == id)
        {
            file.close();
            return true;
        }

    }


    file.close();

    return false;

}



bool IssueManager::bookExists(int id)
{

    Book book;


    ifstream file(BOOK_FILE.c_str(), ios::binary);



    while(file.read((char*)&book,sizeof(Book)))
    {

        if(book.bookId == id)
        {
            file.close();
            return true;
        }

    }


    file.close();


    return false;

}


void IssueManager::updateBookQuantity(int id)
{

    Book book;


    fstream file(BOOK_FILE.c_str(), ios::in | ios::out | ios::binary);



    while(file.read((char*)&book,sizeof(Book)))
    {

        if(book.bookId == id)
        {

            book.available--;

            book.issued++;


            int pos = -1 * sizeof(Book);


            file.seekp(pos, ios::cur);


            file.write((char*)&book,sizeof(Book));


            break;

        }

    }


    file.close();

}

bool IssueManager::bookAlreadyIssued(int bookId, int studentId)
{

    Issue issue;


    ifstream file(ISSUE_FILE.c_str(), ios::binary);



    if(!file)
        return false;



    while(file.read((char*)&issue,sizeof(Issue)))
    {

        if(issue.bookId == bookId &&
           issue.studentId == studentId &&
           issue.returned == false)
        {
            file.close();
            return true;
        }

    }


    file.close();


    return false;

}


void IssueManager::updateBookAfterReturn(int id)
{

    Book book;


    fstream file(BOOK_FILE.c_str(), ios::in | ios::out | ios::binary);



    while(file.read((char*)&book,sizeof(Book)))
    {

        if(book.bookId == id)
        {

            book.available++;

            book.issued--;


            file.seekp(-sizeof(Book), ios::cur);


            file.write((char*)&book,sizeof(Book));


            break;

        }

    }


    file.close();

}


void IssueManager::calculateDueDate(char dueDate[])
{

    time_t now = time(0);


    now = now + (DUE_DAYS * 24 * 60 * 60);


    tm *ltm = localtime(&now);



    sprintf(dueDate,
            "%02d/%02d/%d",
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year);

}


int IssueManager::calculateLateDays(char dueDate[])
{

    int day,month,year;


    sscanf(dueDate,"%d/%d/%d",
           &day,
           &month,
           &year);



    tm due = {0};


    due.tm_mday = day;

    due.tm_mon = month - 1;

    due.tm_year = year - 1900;



    time_t dueTime = mktime(&due);



    time_t now = time(0);



    double diff = difftime(now,dueTime);



    int days = diff / (60*60*24);



    if(days > 0)
        return days;


    return 0;

}

void IssueManager::saveFine(Issue issue)
{

    Fine fine;


    fine.fineId = 1000 + issue.issueId;


    fine.issueId = issue.issueId;


    fine.studentId = issue.studentId;


    fine.amount = issue.fine;



    time_t now = time(0);

    tm *ltm = localtime(&now);



    sprintf(fine.date,
            "%02d/%02d/%d",
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year);



    ofstream file(FINE_FILE.c_str(), ios::binary | ios::app);



    if(file)
    {

        file.write((char*)&fine,sizeof(Fine));

    }



    file.close();

}


void IssueManager::updateStudentFine(int studentId, float amount)
{

    Student student;


    fstream file(STUDENT_FILE.c_str(), ios::in | ios::out | ios::binary);



    while(file.read((char*)&student,sizeof(Student)))
    {

        if(student.studentId == studentId)
        {

            student.fine += amount;


            file.seekp(-sizeof(Student), ios::cur);


            file.write((char*)&student,sizeof(Student));


            break;

        }

    }


    file.close();

}


void IssueManager::clearStudentFine(int studentId)
{

    Student student;


    fstream file(STUDENT_FILE.c_str(), ios::in | ios::out | ios::binary);



    while(file.read((char*)&student,sizeof(Student)))
    {

        if(student.studentId == studentId)
        {

            student.fine = 0;


            file.seekp(-sizeof(Student), ios::cur);


            file.write((char*)&student,sizeof(Student));


            break;

        }

    }


    file.close();

}

void IssueManager::fineMenu()
{

    int choice;


    do
    {

        system("cls");


        Utility::header("FINE MANAGEMENT");


        cout<<"1. View Fine Records"<<endl;

        cout<<"2. Search Student Fine"<<endl;

        cout<<"3. Pay Fine"<<endl;

        cout<<"4. Back"<<endl;



        cout<<"\nEnter Choice : ";

        cin>>choice;



        switch(choice)
        {

        case 1:
            viewFineRecords();
            break;


        case 2:
            searchStudentFine();
            break;


        case 3:
            payFine();
            break;


        case 4:
            break;


        default:
            cout<<"Invalid Choice";

        }


        system("pause");


    }while(choice!=4);

}


void IssueManager::viewFineRecords()
{

    system("cls");


    Utility::header("FINE RECORDS");


    Fine fine;


    ifstream file(FINE_FILE.c_str(), ios::binary);



    if(!file)
    {
        cout<<"No Fine Record Found";
        return;
    }



    while(file.read((char*)&fine,sizeof(Fine)))
    {

        fine.display();

        cout<<"-------------------"<<endl;

    }



    file.close();

}


void IssueManager::searchStudentFine()
{

    int id;


    cout<<"Enter Student ID : ";

    cin>>id;



    Student student;


    ifstream file(STUDENT_FILE.c_str(), ios::binary);



    bool found=false;



    while(file.read((char*)&student,sizeof(Student)))
    {

        if(student.studentId==id)
        {

            cout<<"\nStudent Name : "<<student.name;

            cout<<"\nFine Amount : "<<student.fine;


            found=true;

            break;

        }

    }



    file.close();



    if(!found)
        cout<<"Student Not Found";

}

void IssueManager::payFine()
{

    int id;


    cout<<"Enter Student ID : ";

    cin>>id;



    clearStudentFine(id);



    cout<<"\nFine Cleared Successfully";

}


void IssueManager::searchByIssueID()
{
    system("cls");

    Utility::header("SEARCH BY ISSUE ID");

    int id;

    cout<<"Enter Issue ID : ";
    cin>>id;

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    while(file.read((char*)&issue,sizeof(Issue)))
    {
        if(issue.issueId == id)
        {
            found = true;

            cout<<"\nIssue ID    : "<<issue.issueId;
            cout<<"\nStudent ID  : "<<issue.studentId;
            cout<<"\nBook ID     : "<<issue.bookId;
            cout<<"\nIssue Date  : "<<issue.issueDate;
            cout<<"\nDue Date    : "<<issue.dueDate;
            cout<<"\nReturn Date : ";

            if(issue.returned)
                cout<<issue.returnDate;
            else
                cout<<"Not Returned";

            cout<<"\nFine        : "<<issue.fine;

            cout<<"\nStatus      : ";

            if(issue.returned)
                cout<<"Returned";
            else
                cout<<"Issued";

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nIssue Record Not Found";
    }
}

void IssueManager::searchByStudentID()
{
    system("cls");

    Utility::header("SEARCH BY STUDENT ID");

    int id;

    cout<<"Enter Student ID : ";
    cin>>id;

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Due Date"
        <<setw(12)<<"Status"
        <<setw(10)<<"Fine"
        <<endl;

    cout<<"---------------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue,sizeof(Issue)))
    {
        if(issue.studentId == id)
        {
            found = true;

            cout<<setw(10)<<issue.issueId
                <<setw(10)<<issue.bookId
                <<setw(15)<<issue.issueDate
                <<setw(15)<<issue.dueDate
                <<setw(12)
                <<(issue.returned ? "Returned" : "Issued")
                <<setw(10)
                <<issue.fine
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Issue Record Found For This Student.";
    }
}

void IssueManager::searchByBookID()
{
    system("cls");

    Utility::header("SEARCH BY BOOK ID");

    int id;

    cout<<"Enter Book ID : ";
    cin>>id;

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Due Date"
        <<setw(12)<<"Status"
        <<setw(10)<<"Fine"
        <<endl;

    cout<<"-----------------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue,sizeof(Issue)))
    {
        if(issue.bookId == id)
        {
            found = true;

            cout<<setw(10)<<issue.issueId
                <<setw(12)<<issue.studentId
                <<setw(15)<<issue.issueDate
                <<setw(15)<<issue.dueDate
                <<setw(12)
                <<(issue.returned ? "Returned" : "Issued")
                <<setw(10)
                <<issue.fine
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Issue Record Found For This Book.";
    }
}

void IssueManager::pendingIssues()
{
    system("cls");

    Utility::header("PENDING ISSUES");

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Due Date"
        <<endl;

    cout<<"---------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue, sizeof(Issue)))
    {
        if(issue.returned == false)
        {
            found = true;

            cout<<setw(10)<<issue.issueId
                <<setw(12)<<issue.studentId
                <<setw(10)<<issue.bookId
                <<setw(15)<<issue.issueDate
                <<setw(15)<<issue.dueDate
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Pending Issue Found.";
    }
}

void IssueManager::returnedIssues()
{
    system("cls");

    Utility::header("RETURNED ISSUES");

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Return Date"
        <<setw(10)<<"Fine"
        <<endl;

    cout<<"---------------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue, sizeof(Issue)))
    {
        if(issue.returned)
        {
            found = true;

            cout<<setw(10)<<issue.issueId
                <<setw(12)<<issue.studentId
                <<setw(10)<<issue.bookId
                <<setw(15)<<issue.issueDate
                <<setw(15)<<issue.returnDate
                <<setw(10)<<issue.fine
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Returned Issue Found.";
    }
}


void IssueManager::reportsMenu()
{
    int choice;

    do
    {
        system("cls");

        Utility::header("LIBRARY REPORTS");

        cout<<"1. Total Books"<<endl;
        cout<<"2. Total Students"<<endl;
        cout<<"3. Total Issued Books"<<endl;
        cout<<"4. Total Returned Books"<<endl;
        cout<<"5. Total Fine Collection"<<endl;
        cout<<"6. Most Issued Books"<<endl;
        cout<<"7. Overdue Books"<<endl;
        cout<<"8. Back"<<endl;

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            totalBooksReport();
            break;

        case 2:
            totalStudentsReport();
            break;

        case 3:
            totalIssuedBooksReport();
            break;

        case 4:
            totalReturnedBooksReport();
            break;

        case 5:
            totalFineReport();
            break;

        case 6:
            mostIssuedBooksReport();
            break;

        case 7:
            overdueBooksReport();
            break;

        case 8:
            break;

        default:
            cout<<"Invalid Choice";
        }

        if(choice != 8)
            system("pause");

    }while(choice != 8);
}


void IssueManager::totalBooksReport()
{
    system("cls");

    Utility::header("TOTAL BOOKS REPORT");

    Book book;

    ifstream file(BOOK_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Book File Not Found";
        return;
    }

    int totalTitles = 0;
    int totalQuantity = 0;
    int totalAvailable = 0;
    int totalIssued = 0;

    while(file.read((char*)&book, sizeof(Book)))
    {
        totalTitles++;

        totalQuantity += book.quantity;

        totalAvailable += book.available;

        totalIssued += book.issued;
    }

    file.close();

    cout<<"\nTotal Book Titles : "<<totalTitles<<endl;
    cout<<"Total Book Copies : "<<totalQuantity<<endl;
    cout<<"Available Books   : "<<totalAvailable<<endl;
    cout<<"Issued Books      : "<<totalIssued<<endl;
}

void IssueManager::totalStudentsReport()
{
    system("cls");

    Utility::header("TOTAL STUDENTS REPORT");

    Student student;

    ifstream file(STUDENT_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Student File Not Found";
        return;
    }

    int totalStudents = 0;
    int activeStudents = 0;
    int inactiveStudents = 0;
    float totalFine = 0;

    while(file.read((char*)&student, sizeof(Student)))
    {
        totalStudents++;

        if(student.active)
            activeStudents++;
        else
            inactiveStudents++;

        totalFine += student.fine;
    }

    file.close();

    cout<<"\nTotal Students    : "<<totalStudents<<endl;
    cout<<"Active Students   : "<<activeStudents<<endl;
    cout<<"Inactive Students : "<<inactiveStudents<<endl;
    cout<<"Pending Fine      : Rs. "<<totalFine<<endl;
}

void IssueManager::totalIssuedBooksReport()
{
    system("cls");

    Utility::header("TOTAL ISSUED BOOKS REPORT");

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    int totalIssueRecords = 0;
    int currentlyIssued = 0;
    int returnedBooks = 0;

    while(file.read((char*)&issue, sizeof(Issue)))
    {
        totalIssueRecords++;

        if(issue.returned)
            returnedBooks++;
        else
            currentlyIssued++;
    }

    file.close();

    float returnPercentage = 0;

    if(totalIssueRecords > 0)
    {
        returnPercentage =
            (returnedBooks * 100.0f) / totalIssueRecords;
    }

    cout<<"\nTotal Issue Records : "<<totalIssueRecords<<endl;
    cout<<"Currently Issued    : "<<currentlyIssued<<endl;
    cout<<"Returned Books      : "<<returnedBooks<<endl;
    cout<<"Return Percentage   : "
        <<fixed<<setprecision(2)
        <<returnPercentage<<" %"<<endl;
}

void IssueManager::totalReturnedBooksReport()
{
    system("cls");

    Utility::header("RETURNED BOOKS REPORT");

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Issue Date"
        <<setw(15)<<"Return Date"
        <<setw(10)<<"Fine"
        <<endl;

    cout<<"--------------------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue,sizeof(Issue)))
    {
        if(issue.returned)
        {
            found = true;

            cout<<setw(10)<<issue.issueId
                <<setw(12)<<issue.studentId
                <<setw(10)<<issue.bookId
                <<setw(15)<<issue.issueDate
                <<setw(15)<<issue.returnDate
                <<setw(10)<<issue.fine
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Returned Books Found.";
    }
}

void IssueManager::totalFineReport()
{
    system("cls");

    Utility::header("TOTAL FINE REPORT");

    Fine fine;

    ifstream file(FINE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"No Fine Record Found";
        return;
    }

    int totalRecords = 0;
    float totalFine = 0;
    float highestFine = 0;
    float lowestFine = 0;

    while(file.read((char*)&fine, sizeof(Fine)))
    {
        totalRecords++;

        totalFine += fine.amount;

        if(totalRecords == 1)
        {
            highestFine = fine.amount;
            lowestFine = fine.amount;
        }

        if(fine.amount > highestFine)
            highestFine = fine.amount;

        if(fine.amount < lowestFine)
            lowestFine = fine.amount;
    }

    file.close();

    float averageFine = 0;

    if(totalRecords > 0)
        averageFine = totalFine / totalRecords;

    cout<<"\nTotal Fine Records : "<<totalRecords<<endl;
    cout<<"Total Collection   : Rs. "<<totalFine<<endl;
    cout<<"Highest Fine       : Rs. "<<highestFine<<endl;
    cout<<"Lowest Fine        : Rs. "<<lowestFine<<endl;
    cout<<"Average Fine       : Rs. "<<fixed<<setprecision(2)<<averageFine<<endl;
}

void IssueManager::mostIssuedBooksReport()
{
    system("cls");

    Utility::header("MOST ISSUED BOOKS REPORT");

    Book book;

    ifstream file(BOOK_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Book File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Book ID"
        <<setw(30)<<"Title"
        <<setw(20)<<"Author"
        <<setw(10)<<"Issued"
        <<endl;

    cout<<"--------------------------------------------------------------------------"<<endl;

    while(file.read((char*)&book,sizeof(Book)))
    {
        if(book.issued > 0)
        {
            found = true;

            cout<<setw(10)<<book.bookId
                <<setw(30)<<book.title
                <<setw(20)<<book.author
                <<setw(10)<<book.issued
                <<endl;
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Book Has Been Issued Yet.";
    }
}

void IssueManager::overdueBooksReport()
{
    system("cls");

    Utility::header("OVERDUE BOOKS REPORT");

    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
    {
        cout<<"Issue File Not Found";
        return;
    }

    bool found = false;

    cout<<left;

    cout<<setw(10)<<"Issue ID"
        <<setw(12)<<"Student ID"
        <<setw(10)<<"Book ID"
        <<setw(15)<<"Due Date"
        <<setw(10)<<"Late Days"
        <<setw(10)<<"Fine"
        <<endl;

    cout<<"--------------------------------------------------------------------------"<<endl;

    while(file.read((char*)&issue, sizeof(Issue)))
    {
        if(!issue.returned)
        {
            int lateDays = calculateLateDays(issue.dueDate);

            if(lateDays > 0)
            {
                found = true;

                cout<<setw(10)<<issue.issueId
                    <<setw(12)<<issue.studentId
                    <<setw(10)<<issue.bookId
                    <<setw(15)<<issue.dueDate
                    <<setw(10)<<lateDays
                    <<setw(10)<<(lateDays * FINE_PER_DAY)
                    <<endl;
            }
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nNo Overdue Books Found.";
    }
}


bool IssueManager::canIssueMoreBooks(int studentId)
{
    Issue issue;

    ifstream file(ISSUE_FILE.c_str(), ios::binary);

    if(!file)
        return true;

    int count = 0;

    while(file.read((char*)&issue, sizeof(Issue)))
    {
        if(issue.studentId == studentId &&
           issue.returned == false)
        {
            count++;
        }
    }

    file.close();

    return (count < MAX_BOOK_ISSUE);
}


bool IssueManager::bookAvailable(int id)
{
    Book book;

    ifstream file(BOOK_FILE.c_str(), ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&book, sizeof(Book)))
    {
        if(book.bookId == id)
        {
            file.close();

            return (book.available > 0);
        }
    }

    file.close();

    return false;
}


bool IssueManager::isStudentActive(int id)
{
    Student student;

    ifstream file(STUDENT_FILE.c_str(), ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&student, sizeof(Student)))
    {
        if(student.studentId == id)
        {
            file.close();

            return student.active;
        }
    }

    file.close();

    return false;
}

bool IssueManager::hasPendingFine(int studentId)
{
    Student student;

    ifstream file(STUDENT_FILE.c_str(), ios::binary);

    if(!file)
        return false;

    while(file.read((char*)&student, sizeof(Student)))
    {
        if(student.studentId == studentId)
        {
            file.close();

            return (student.fine > 0);
        }
    }

    file.close();

    return false;
}

