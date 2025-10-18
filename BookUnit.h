#ifndef CURSEWORK_OOP_SPBPU_BOOKUNIT_H
#define CURSEWORK_OOP_SPBPU_BOOKUNIT_H
#include <string>
#include <vector>

using namespace std;


//
// Classes
//
class FullName {
private:
public:
    string name_;
    string surname_;
    string patronymic_;
public:
    FullName(string& name, string& surname, string& patronymic);
};

class BirthDate {
private:
public:
    int day_;
    int month_;
    int year_;
    bool checkBirthDate(const int& day, const int& month, const int& year) const;
public:
    BirthDate(const int& day, const int& month, const int& year);
    void printBirthDate() const;
};

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
};

class BookUnit {
private:
public:
    FullName fullName;
    Address address;
    const BirthDate birthDate;
    string email;
    vector<string> phoneNumber;
public:
    BookUnit(FullName& fullName, Address& address, BirthDate birthDate, string email, vector<string>& phoneNumber);
    void addPhoneNumber(const string& phoneNumber);
    void setFullName(FullName &full);
    FullName& getFullName();


};

//
// Methods
//
void deleteExtraSpace(string& element);
bool checkFullName(const string& element);
FullName* createFullName(string& name, string& surname, string& patronymic);

bool checkEmail(const string& email);
bool checkPhoneNumber(const string& phoneNumber);

#endif //CURSEWORK_OOP_SPBPU_BOOKUNIT_H