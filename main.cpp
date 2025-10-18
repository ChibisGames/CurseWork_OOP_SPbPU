#include "BookUnit.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    auto date = new BirthDate(1, 1, 2000);
    cout << 12222222;
    date->printBirthDate();
    cout << 22222221 << endl;
/*

    string str= "   qSTR w   eSTR  ";
    deleteExtraSpace(str);
    cout << str << endl;


    string n = "   Q w e ";
    string s = "   W e q ";
    string p = "   E q w ";
    auto fullname = createFullName(n,s,p);
    cout << fullname->name_ << ", " << fullname->surname_ << ", " << fullname->patronymic_ << endl;

    string country = "Rus";
    string region = "SPb";
    string city = "SPb";
    string street = "Stoykost";
    string house = "26";
    string corpus = "3";
    string flat = "346";
    auto address = new Address(country, region, city, street, house, corpus, flat);

    string email = "sobaka@bk.ru";

    auto phoneNumber = new vector<string>;
    phoneNumber->emplace_back("89643222467");

    auto firstBook = new BookUnit(*fullname, *address, *date, email, *phoneNumber);

    cout << "PhoneNumber: " << firstBook->phoneNumber.back() << endl;

    delete firstBook;
    delete fullname;
    delete address;
    delete date;
    delete phoneNumber;*/

    return 0;

}

void menu(int& opt) {
    // TODO: make menu
}