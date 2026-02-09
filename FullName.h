#ifndef CURSEWORK_OOP_SPBPU_FULLNAME_H
#define CURSEWORK_OOP_SPBPU_FULLNAME_H

#include "AllModuls.h"
#include "BookUnit.h"


using namespace std;

bool checkNameElement(const string& element);

bool checkFullName(const vector<string>& fullname);

void deleteExtraSpaceInFullName(string& element);

void refactorFullName(BookUnit& unit);


#endif //CURSEWORK_OOP_SPBPU_FULLNAME_H