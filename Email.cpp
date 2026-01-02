#include "AllModuls.h"
#include "Email.h"

using namespace std;

bool checkEmail(string& email, BookUnit& unit) {
    const regex re(R"(^[A-Za-z0-9]+@[A-Za-z0-9]+@[A-Za-z0-9]+\.[A-Za-z]$))");
    deleteExtraSpaceInEmail(email);

    string e = email;
    auto pos = e.find('@');
    e = e.substr(0, pos);
    transform(e.begin(), e.end(), e.begin(),
        [](unsigned char c) { return tolower(c); });


    string name = (*unit.getFullName())[0];
    transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c) { return tolower(c); });

    bool nameInEmail = e.find(name) != string::npos;

    return regex_match(email, re) * nameInEmail;
}

void deleteExtraSpaceInEmail(string& element) {
    string newElement;
    for (const auto& word : element) {
        if (word != ' ') {newElement.push_back(word);}
    }
    element = newElement;
}

void refactorEmail(BookUnit& unit) {
    int opt = 0;
    auto email = unit.getEmail();
    string newElement;
    while (opt != 2) {
        cout << "1: Изменить email" << endl;
        cout << "2: Выйти из окна изменения email" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        if (opt == 1) {
            cout << "Новый email: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> newElement;
            if (checkEmail(newElement, unit)) {
                (*email) = newElement;
            } else {
                cout << "Некорректно введенный email!" << endl;
                cout << "P.s. проверьте наличие имени в email!" << endl;
            }
            break;
        }
        if (opt != 1 && opt != 2) {
            cout << "Нет такой опции!" << endl;
            break;
        }
    }
}