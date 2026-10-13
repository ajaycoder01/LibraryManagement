📚 Library Management System

A Library Management System developed using C++ to manage library operations such as book management, student records, book issuing and returning, fine management, and report generation.

This project is designed to simplify library administration and maintain records through a file-based data storage system.

✨ Features
Admin Management – Manage library administration.
Book Management – Add, manage, and maintain book records.
Student Management – Maintain student information and records.
Issue & Return Management – Handle book issuing and returning operations.
Fine Management – Manage fines related to library operations.
Report Generation – Generate reports for library records.
Login System – Provide login functionality.
File-Based Storage – Store application data in .dat files.
🛠️ Technologies Used
Programming Language: C++
Concepts: Object-Oriented Programming (OOP), File Handling, Modular Programming
Build Tools: Makefile / Dev-C++
Data Storage: File-based storage using .dat files
📁 Project Structure
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
├── LibraryManagementSystem.dev
├── LibraryManagementSystem.exe
├── LibraryManagementSystem.layout
├── Makefile.win
├── preprocessed.cpp
└── README.md

⚙️ Getting Started
Prerequisites

Make sure you have a C++ compiler installed, such as GCC or MinGW.

Clone the Repository
git clone https://github.com/YOUR-USERNAME/LibraryManagement.git


Navigate to the project directory:

cd LibraryManagement

Compile the Project

If your environment supports GCC, you can compile the source files using:

g++ main.cpp src/*.cpp -Iinclude -o LibraryManagement

Run the Application

On Windows:

LibraryManagement.exe


On Linux/macOS:

./LibraryManagement


Note: Build commands may need adjustment depending on your compiler, operating system, and project configuration.

💾 Data Storage

The application uses .dat files to store library information:

books.dat – Book records
students.dat – Student records
issue.dat – Book issue records
fine.dat – Fine records

Keep these data files in the expected directory so the application can access its records correctly.

🎯 Project Objectives
Simplify library management operations.
Maintain book and student records efficiently.
Manage book issuing, returns, and fines.
Demonstrate practical implementation of C++ and file handling.
Organize code into separate header and source files for better maintainability.
🚀 Future Enhancements
Database integration using MySQL or SQLite.
Improved user interface.
Search and filter functionality.
Book availability tracking.
Automated fine calculation.
Enhanced authentication and access control.
👨‍💻 Author

Your Name

GitHub: YOUR-USERNAME
📄 License

This project is available for educational and learning purposes. Add a suitable open-source license if you intend to distribute it publicly.

⭐ If you find this project useful, consider giving the repository a star!
