#ifndef CURSEWORK_OOP_SPBPU_BIRTHDATE_H
#define CURSEWORK_OOP_SPBPU_BIRTHDATE_H

#include "AllModuls.h"
#include "BookUnit.h"

using namespace std;

bool checkBirthDate(const vector<int>& birthdate);

bool isLeapYear(const int& year);

int daysInMonth(const vector<int>& birthDate);

void setCurrentDate(vector<int>& currentDate);


void refactorBirthDate(BookUnit& unit);

#endif //CURSEWORK_OOP_SPBPU_BIRTHDATE_H