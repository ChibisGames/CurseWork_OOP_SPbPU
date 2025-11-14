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

void BookUnit::addOrChangeFullName(const vector<string> &newFullName) {
    fullName = newFullName;
}

void BookUnit::addOrChangeAddress(const vector<string> &newAddress) {
    address = newAddress;
}

void BookUnit::addOrChangeBirthDate(const vector<int> &newBirthDate) {
    birthDate = newBirthDate;
}

void BookUnit::addOrChangeEmail(const string &newEmail) {
    email = newEmail;
}

void BookUnit::addPhoneNumber(const string& newPhoneNumber) {
    phoneNumber.push_back(newPhoneNumber);
}

void BookUnit::changePhoneNumber(const string& changePhoneNumber, int pos) {
    auto iter = phoneNumber.begin();
    advance(iter, pos);
    if (changePhoneNumber == "-" && phoneNumber.size() == 1) {
        cout << "Нельзя удалить единственный номер!" << endl;
    }else if (changePhoneNumber == "-") {
        phoneNumber.erase(iter);
    }else {
        *iter = changePhoneNumber;
    }
}

void BookUnit::sortPhoneNumbers() {
    phoneNumber.sort();
}

void BookUnit::printPhoneNumbers() {
    cout << "Список всех телефонных номеров человека: " << endl;
    auto iter = phoneNumber.begin();
    for (int i = 0; i < phoneNumber.size(); i++) {
        advance(iter, i);
        cout << i + 1 << ") " << *iter << endl;
    }
}

vector<string>* BookUnit::getFullName() {return &fullName; }
vector<string>* BookUnit::getAddress() {return &address; }
vector<int>* BookUnit::getBirthDate() {return &birthDate; }
string* BookUnit::getEmail() {return &email; }
list<string>* BookUnit::getPhoneNumber() {return &phoneNumber;}

int BookUnit::getPhoneNumberSize() {return phoneNumber.size();}

bool BookUnit::isEmpty() const {
    return email.empty();
}

void BookUnit::printBook() const {
    for (int i = 0; i < 3; ++i) {
        cout << fullName[i] << " ";
    }
    cout << "// ";

    for (int i = 0; i < 7; ++i) {
        cout << address[i] << " ";
    }
    cout << "// ";

    cout << birthDate[0] << " " << MONTH[birthDate[1]] << " " << birthDate[2] << " ";
    cout << "// ";

    cout << email << " // ";

    // Сделал for-цикл, потому что CLion выдавал Clang-Tidy: "Use range-based for loop"
    for (const auto& iter : phoneNumber) {
        cout << iter << " ";
    }
    cout << endl;
}

void BookUnit::createBook(const BookUnit& book) {
    fullName = book.fullName;
    address = book.address;
    birthDate = book.birthDate;
    email = book.email;
    phoneNumber = book.phoneNumber;
}
