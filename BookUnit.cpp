#include "BookUnit.h"
#include "AllModuls.h"

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
void BookUnit::addFullName(const vector<string> &newFullName) {
    fullName = newFullName;
}

void BookUnit::addAddress(const vector<string> &newAddress) {
    address = newAddress;
}

void BookUnit::addBirthDate(const vector<int> &newBirthDate) {
    birthDate = newBirthDate;
}

void BookUnit::addEmail(const string &newEmail) {
    email = newEmail;
}

void BookUnit::addPhoneNumber(const string& newPhoneNumber) {
    phoneNumber.push_back(newPhoneNumber);
}

void BookUnit::printBook() const {
    for (int i = 0; i < 3; ++i) {
        cout << fullName[0] << " ";
    }
    cout << "// ";

    for (int i = 0; i < 7; ++i) {
        cout << address[i] << " ";
    }
    cout << "// ";

    for (int i = 0; i < 3; ++i) {
        cout << birthDate[0] << " ";
    }
    cout << "// ";

    cout << email << " // ";

    // Сделал for-цикл, потому что CLion выдавал Clang-Tidy: "Use range-based for loop"
    for (const auto& iter : phoneNumber) {
        cout << iter << " ";
    }
    cout << "// ";
}

void BookUnit::createAndRefactorBook(const BookUnit& book) {
    fullName = book.fullName;
    address = book.address;
    birthDate = book.birthDate;
    email = book.email;
    phoneNumber = book.phoneNumber;
}
