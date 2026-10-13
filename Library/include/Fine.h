#ifndef FINE_H
#define FINE_H

#include "Constants.h"


class Fine
{

public:

    int fineId;

    int issueId;

    int studentId;

    float amount;


    char date[20];


    Fine();

    void display();

};


#endif
