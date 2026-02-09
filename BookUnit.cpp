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

void BookUnit::toFormat(string &newPhoneNumber) {
    string copyNewPhoneNumber;
    auto iter = newPhoneNumber.begin();
    copyNewPhoneNumber.push_back(*iter);
    advance(iter, 1);
    for (iter; iter != newPhoneNumber.end(); ++iter) {
        if (isdigit(*iter)) {copyNewPhoneNumber.push_back(*iter);}
    }
    newPhoneNumber = copyNewPhoneNumber;
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

unsigned int BookUnit::getPhoneNumberSize() const {return phoneNumber.size();}

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

string BookUnit::toString() const {
    stringstream ss;

    // Записываем полное имя
    for (size_t i = 0; i < fullName.size(); ++i) {
        ss << fullName[i];
        if (i < fullName.size() - 1) ss << "|";
    }
    ss << "/";

    // Записываем адрес
    for (size_t i = 0; i < address.size(); ++i) {
        ss << address[i];
        if (i < address.size() - 1) ss << "|";
    }
    ss << "/";

    // Записываем дату рождения
    for (size_t i = 0; i < birthDate.size(); ++i) {
        ss << birthDate[i];
        if (i < birthDate.size() - 1) ss << "|";
    }
    ss << "/";

    // Записываем email
    ss << email << "/";

    // Записываем номера телефонов
    size_t count = 0;
    for (const auto& phone : phoneNumber) {
        ss << phone;
        if (++count < phoneNumber.size()) ss << "|";
    }

    return ss.str();
}

void BookUnit::fromString(const string& data) {
    stringstream ss(data);
    string token;

    // Читаем полное имя
    if (getline(ss, token, '/')) {
        stringstream nameStream(token);
        string namePart;
        int i = 0;
        while (getline(nameStream, namePart, '|') && i < 3) {
            fullName[i++] = namePart;
        }
    }

    // Читаем адрес
    if (getline(ss, token, '/')) {
        stringstream addrStream(token);
        string addrPart;
        int i = 0;
        while (getline(addrStream, addrPart, '|') && i < 7) {
            address[i++] = addrPart;
        }
    }

    // Читаем дату рождения
    if (getline(ss, token, '/')) {
        stringstream dateStream(token);
        string datePart;
        int i = 0;
        while (getline(dateStream, datePart, '|') && i < 3) {
            birthDate[i++] = stoi(datePart);
        }
    }

    getline(ss, email, '/');

    if (getline(ss, token)) {
        phoneNumber.clear();
        stringstream phoneStream(token);
        string phone;
        while (getline(phoneStream, phone, '|')) {
            phoneNumber.push_back(phone);
        }
    }
};
