#ifndef CURSEWORK_OOP_SPBPU_CHECKMETHODS_H
#define CURSEWORK_OOP_SPBPU_CHECKMETHODS_H

#include "BookUnit.h"
#include "AllModuls.h"

using namespace std;


bool checkFullName(const vector<string>& fullname);

bool checkBirthDate(const vector<int>& birthdate);

bool checkEmail(const string& email);

bool checkPhoneNumber(const string& phoneNumber);

bool checkRequiredFields(const BookUnit& unit);


void deleteExtraSpace(string& element);

void printBookUnits(const list<BookUnit>& units);
void createNewBook(list<BookUnit>& unit);
void refactorBook(list<BookUnit>& unit);
void deleteBook(list<BookUnit>& units);

void sortData(list<BookUnit>& unit, int sortField);

#endif //CURSEWORK_OOP_SPBPU_CHECKMETHODS_H