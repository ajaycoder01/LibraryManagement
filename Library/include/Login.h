#ifndef LOGIN_H
#define LOGIN_H

#include "Student.h"
#include "Constants.h"
#include "Utility.h"

class Login
{
public:

    bool adminLogin();

   bool studentLogin(Student &student);

};

#endif
