#ifndef CURSEWORK_OOP_SPBPU_BOOKUNIT_H
#define CURSEWORK_OOP_SPBPU_BOOKUNIT_H

#include "AllModuls.h"

using namespace std;


//
// Classes
//
/*
class Address {
private:
public:
    string country;
    string region;
    string city;
    string street;
    string house;
    string corpus;
    string flat;
    bool checkAddress(const string& address) const;
public:
    Address(const string& country, const string& region, const string& city, const string& street,
        const string& house, const string& corpus, const string& flat);
};*/

class BookUnit {
private:
    vector<string> fullName = vector<string>(3);
    vector<string> address = vector<string>(7);
    vector<int> birthDate = vector<int>( 3);
    string email;
    list<string> phoneNumber;
public:
    void addFullName(const vector<string>& newFullName);
    void addAddress(const vector<string>& newAddress);
    void addBirthDate(const vector<int>& newBirthDate);
    void addEmail(const string& newEmail);
    void addPhoneNumber(const string& newPhoneNumber);

    void printBook() const;
    void createAndRefactorBook(const BookUnit& book);
};

#endif //CURSEWORK_OOP_SPBPU_BOOKUNIT_H