#ifndef CURSEWORK_OOP_SPBPU_CHECKMETHODS_H
#define CURSEWORK_OOP_SPBPU_CHECKMETHODS_H

#include "BookUnit.h"

#include "AllModuls.h"

using namespace std;

int mainManu(int& opt);

void printBookUnits(const list<BookUnit>& units);

void createNewBook(list<BookUnit>& units);

void refactorBook(list<BookUnit>& units);

void deleteBook(list<BookUnit>& units);

void sortData(list<BookUnit>& units);

string toLower(const string& str);

bool isNumber(const string& str);

void findData(list<BookUnit>& units);

void readFile(list<BookUnit>& units);

void writeFile(const list<BookUnit>& units);

#endif //CURSEWORK_OOP_SPBPU_CHECKMETHODS_H