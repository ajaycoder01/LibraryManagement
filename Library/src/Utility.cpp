#include "../include/Utility.h"

void Utility::line()
{
    cout << "=====================================================\n";
}

void Utility::header(string title)
{
    line();

    cout << "\t" << title << endl;

    line();
}

void Utility::pressEnter()
{
    cout << "\nPress Enter To Continue...";
    cin.ignore(); // Input buffer me jo extra characters hain unko remove karta hai.
    cin.get(); // User ke Enter press karne ka wait karega.
}

int Utility::currentDay()
{
    time_t now = time(0);

    tm *ltm = localtime(&now);

    return ltm->tm_mday;
}
