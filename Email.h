#ifndef CURSEWORK_OOP_SPBPU_EMAIL_H
#define CURSEWORK_OOP_SPBPU_EMAIL_H

#include "AllModuls.h"
#include "BookUnit.h"


using namespace std;


bool checkEmail(string& email, BookUnit& unit);

void deleteExtraSpaceInEmail(string& element);

void refactorEmail(BookUnit& unit);


#endif //CURSEWORK_OOP_SPBPU_EMAIL_H