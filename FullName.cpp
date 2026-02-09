#include "AllModuls.h"
#include "FullName.h"
#include "BookUnit.h"
#include "Email.h"

using namespace std;

bool checkNameElement(const string& element) {
    const regex re(R"(^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё0-9\-]*[A-Za-zА-Яа-яЁё0-9]?$)");
    return regex_match(element, re);
}

bool checkFullName(const vector<string>& fullname) {
    bool flag = true;
    for (const auto& element : fullname) {
        flag *= checkNameElement(element);
    }
    return flag;
}

void deleteExtraSpaceInFullName(string& element) {
    // Удаление пробелов перед словом
    element.erase(element.begin(), find_if(element.begin(), element.end(), [](char c) {
        return c != ' ';
    }));
    // Удаление пробелов после слова
    element.erase(find_if(element.rbegin(), element.rend(), [](char c) {
        return c != ' ';
    }).base(), element.end());

    //Сводит пробелы в слове в 1
    bool flag = false;
    string newElement;
    newElement.reserve(element.size());
    for (const auto& word : element) {
        if (word == ' ') {
            if (!flag) {
                newElement.push_back(word);
                flag = true;
            }
        } else {
            newElement.push_back(word);
            flag = false;
        }
    }
    element = newElement;
}

void refactorFullName(BookUnit& unit) {
    int opt = 0;
    auto fullName = unit.getFullName();
    string newElement;
    auto email = unit.getEmail();
    auto e = *email;
    while (opt != 4) {
        cout << "1: Изменить имя" << endl;
        cout << "2: Изменить фамилию" << endl;
        cout << "3: Изменить отчество" << endl;
        cout << "4: Выйти из окна изменения ФИО" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "Новое имя: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                if (checkNameElement(newElement)) {
                    (*fullName)[0] = newElement;
                } else {
                    cout << "Некорректно введено имя!" << endl;
                }

                while (!checkEmail(e, unit)) {
                    cout << "Новый email должен содержать имя пользователя!" << endl;
                    cout << "Новый email: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> e;
                }
                (*email) = e;
                break;
            case 2:
                cout << "Новая фамилия: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                if (checkNameElement(newElement)) {
                    (*fullName)[1] = newElement;
                } else {
                    cout << "Некорректно введена фамилия!" << endl;
                }
                break;
            case 3:
                cout << "Новое отчество: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                if (checkNameElement(newElement)) {
                    (*fullName)[2] = newElement;
                } else {
                    cout << "Некорректно введено отчество!" << endl;
                }
                break;
            default:
                cout << "Нет такой опции!" << endl;
                break;
        }
    }
}