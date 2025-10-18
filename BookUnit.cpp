#include "BookUnit.h"
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;
//
// Global parameters
//
map<int, string> MONTH = {
    {1, "January"},
    {2, "February"},
    {3, "March"},
    {4, "April"},
    {5, "May"},
    {6, "June"},
    {7, "July"},
    {8, "August"},
    {9, "September"},
    {10, "October"},
    {11, "November"},
    {12, "December"}
};

//
// Classes
//
FullName::FullName(string &name, string &surname, string &patronymic) : name_(name), surname_(surname),
patronymic_(patronymic) {}

bool BirthDate::checkBirthDate(const int &day, const int &month, const int &year) const {
    // TODO: make this part
    return true;
}

BirthDate::BirthDate(const int &day, const int &month, const int &year) {
    if (checkBirthDate(day, month, year)) {
        day_ = day;
        month_ = month;
        year_ = year;
    }else {
        cout << "Birth date is invalid" << endl;
    }
}

void BirthDate::printBirthDate() const{
    printf("%d %s %d (%d.%d.%d)", day_, MONTH[month_].c_str(), year_, day_, month_, year_);
}

Address::Address(const string& country, const string& region, const string& city, const string& street,
    const string& house, const string& corpus, const string& flat) : country(country), region(region),
city(city), street(street), house(house), corpus(corpus), flat(flat) {}


BookUnit::BookUnit(FullName& fullName, Address& address, BirthDate birthDate, string email, vector<string>& phoneNumber)
: fullName(fullName), address(address), birthDate(birthDate), email(email), phoneNumber(phoneNumber) {}

void BookUnit::addPhoneNumber(const string& phonenumber) {
    phoneNumber.push_back(phonenumber);
}


//
// Methods
//
void deleteExtraSpace(string& element) {
    element.erase(element.begin(), find_if(element.begin(), element.end(), [](char c) {
        return c != ' ';
    }));
    element.erase(find_if(element.rbegin(), element.rend(), [](char c) {
        return c != ' ';
    }).base(), element.end());
}
bool checkFullName(const string& element) {
    bool flag = true;
    flag *= isalpha(element[0]) && element.back() != '-';

    if (flag) {return true;}
    return false;
}
FullName* createFullName(string& name, string& surname, string& patronymic) {
    deleteExtraSpace(name);
    deleteExtraSpace(surname);
    deleteExtraSpace(patronymic);
    if (checkFullName(name)) {
        if (checkFullName(surname)) {
            if (checkFullName(patronymic)) {
                auto *fullName = new FullName(name, surname, patronymic);
                return fullName;
            }else {
                cout << "Incorrect patronymic" << endl;
            }
        }else {
            cout << "Incorrect surname" << endl;
        }
    }else {
        cout << "Incorrect name" << endl;
    }
    return nullptr;
}


bool checkEmail(const string& email) {
    // TODO: make this part
    return true;
}
bool checkPhoneNumber(const string& phoneNumber) {
    // TODO: make this part
    return true;
}

