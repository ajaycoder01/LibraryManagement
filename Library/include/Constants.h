#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <fstream>
#include <iomanip>  // Output formatting ke liye. (Table alignment.)
#include <string>
#include <vector>  // Dynamic array ke liye.
#include <ctime>  // Date aur time functions ke liye.
#include <cstdlib>  // General utility functions ke liye.  (rand(), srand(),exit(),system())

using namespace std;

//----------------------
// Login Credentials
//----------------------
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

//----------------------
// File Names
//----------------------
const string BOOK_FILE = "data/books.dat";
const string STUDENT_FILE = "data/students.dat";
const string ISSUE_FILE = "data/issue.dat";
const string HISTORY_FILE = "data/history.dat";
const string FINE_FILE = "data/fine.dat";
const string ADMIN_FILE = "data/admin.dat";

//----------------------
// Library Rules
//----------------------
const int MAX_BOOK_ISSUE = 3;
const int DUE_DAYS = 7;
const int FINE_PER_DAY = 5;

#endif
