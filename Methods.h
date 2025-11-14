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

vector<BookUnit>& readFile();

void writeFile(list<BookUnit>& units);

void sortData(list<BookUnit>& units, int sortField);

void findData(list<BookUnit>& units, int findField);

#endif //CURSEWORK_OOP_SPBPU_CHECKMETHODS_H