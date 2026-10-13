📚 Library Management System

A Library Management System developed using C++ to manage books, students, book issuing and returning, fines, and reports.

✨ Features
```
• Admin Management – Manage library administration.
• Book Management – Add and maintain book records.
• Student Management – Maintain student information and records.
• Book Issue & Return – Handle book issuing and returning operations.
• Fine Management – Manage fines related to library operations.
• Report Generation – Generate reports for library records.
• Login System – Provide login functionality.
• File-Based Storage – Store application data in .dat files.
🛠️ Technologies Used
• Programming Language: C++
• Concepts: Object-Oriented Programming (OOP), File Handling, Modular Programming
• Build Tools: Dev-C++, Makefile
• Data Storage: File-based storage using .dat files
```
📁 Project Structure
```
Library/
│
├── data/
│   ├── books.dat
│   ├── fine.dat
│   ├── issue.dat
│   └── students.dat
│
├── include/
│   ├── Admin.h
│   ├── Book.h
│   ├── BookManager.h
│   ├── Constants.h
│   ├── Fine.h
│   ├── Issue.h
│   ├── IssueManager.h
│   ├── Library.h
│   ├── Login.h
│   ├── Report.h
│   ├── Student.h
│   ├── StudentManager.h
│   └── Utility.h
│
├── src/
│   ├── Admin.cpp
│   ├── Book.cpp
│   ├── BookManager.cpp
│   ├── Fine.cpp
│   ├── Issue.cpp
│   ├── IssueManager.cpp
│   ├── Library.cpp
│   ├── Login.cpp
│   ├── Report.cpp
│   ├── Student.cpp
│   ├── StudentManager.cpp
│   └── Utility.cpp
│
├── main.cpp
├── Makefile.win
└── README.md
```
⚙️ Getting Started
Prerequisites

Install a C++ compiler such as GCC or MinGW.

1. Clone the Repository
git clone https://github.com/YOUR-USERNAME/LibraryManagement.git
cd LibraryManagement

2. Compile the Project
g++ main.cpp src/*.cpp -Iinclude -o LibraryManagement

3. Run the Application

Windows:

LibraryManagement.exe


Linux/macOS:

./LibraryManagement

Note: The build command may need adjustments depending on your compiler and project configuration.
💾 Data Storage

The application stores library information in .dat files.
```
File	Description
• books.dat	Book records
• students.dat	Student records
• issue.dat	Book issue records
• fine.dat	Fine records

🎯 Project Objectives
- Simplify library management operations.
- Maintain book and student records efficiently.
- Manage book issuing, returns, and fines.
- Demonstrate C++ programming and file handling.
- Organize code using header and source files.
```
👨‍💻 Author

Your Name

GitHub: YOUR-USERNAME
📄 License

This project is intended for educational purposes. Add a suitable open-source license if you plan to distribute it publicly.

⭐ If you find this project useful, consider giving it a star!
