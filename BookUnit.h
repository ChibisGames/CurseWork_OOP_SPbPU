#ifndef CURSEWORK_OOP_SPBPU_BOOKUNIT_H
#define CURSEWORK_OOP_SPBPU_BOOKUNIT_H

#include "AllModuls.h"

using namespace std;


class BookUnit {
private:
    vector<string> fullName = vector<string>(3);
    vector<string> address = vector<string>(7);
    vector<int> birthDate = vector<int>( 3);
    string email;
    list<string> phoneNumber;
public:
    void addOrChangeFullName(const vector<string>& newFullName);
    void addOrChangeAddress(const vector<string>& newAddress);
    void addOrChangeBirthDate(const vector<int>& newBirthDate);
    void addOrChangeEmail(const string& newEmail);
    static void toFormat(string &phoneNumber); // для приведения в един. форму телефона
    void addPhoneNumber(const string& newPhoneNumber);
    void changePhoneNumber(const string& changePhoneNumber, int pos);
    void sortPhoneNumbers();
    void printPhoneNumbers();

    vector<string>* getFullName();
    vector<string>* getAddress();
    vector<int>* getBirthDate();
    string* getEmail();
    list<string>* getPhoneNumber();
    unsigned int getPhoneNumberSize() const;

    bool isEmpty() const;
    void printBook() const;
    void createBook(const BookUnit& book);

    string toString() const;
    void fromString(const string& data);
};

#endif //CURSEWORK_OOP_SPBPU_BOOKUNIT_H
