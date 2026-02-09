#include "AllModuls.h"
#include "BirthDate.h"

using namespace std;

bool checkBirthDate(const vector<int>& birthdate) {
    auto currentDate = vector<int>(3);
    setCurrentDate(currentDate);

    if (birthdate[2] < 1 || birthdate[2] > currentDate[2]) {return false;}
    if (birthdate[1] < 1 || birthdate[1] > 12) {return false;}
    if (birthdate[0] < 1 || birthdate[0] > daysInMonth(birthdate)) {return false;}

    if (birthdate[2] == currentDate[2]) {
        if (birthdate[1] > currentDate[1]) {return false;}
        else if (birthdate[1] == currentDate[1]) {
            if (birthdate[0] >= currentDate[0]) {return false;}
        }
    }
    return true;
}

bool isLeapYear(const int& year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(const vector<int>& birthDate) {
    const int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (birthDate[1] == 2) return mdays[1] + (isLeapYear(birthDate[2]) ? 1 : 0);
    return mdays[birthDate[1] - 1];
}

void setCurrentDate(vector<int>& currentDate) {
    const time_t now = time(nullptr);
    const tm local = *localtime(&now);
    currentDate[0] = local.tm_mday;
    currentDate[1] = local.tm_mon + 1;
    currentDate[2] = local.tm_year + 1900;
}

void refactorBirthDate(BookUnit& unit) {
    int opt = 0;
    auto birthDate = unit.getBirthDate();
    auto newBirthDate = vector<int>(3);
    string newElement;
    int newElementInt;
    while (opt != 4) {
        cout << "1: Изменить день" << endl;
        cout << "2: Изменить месяц" << endl;
        cout << "3: Изменить год" << endl;
        cout << "4: Выйти из окна изменения даты рождения" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        newBirthDate = *birthDate;
        switch (opt) {
            case 1:
                cout << "Новый день: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                newElementInt = stoi(newElement);
                newBirthDate[0] = newElementInt;
                if (checkBirthDate(newBirthDate)) {
                    (*birthDate)[0] = newElementInt;
                } else {
                    cout << "Некорректно введенный день!" << endl;
                }
                break;
            case 2:
                cout << "Новый месяц: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                newElementInt = stoi(newElement);
                newBirthDate[1] = newElementInt;
                if (checkBirthDate(newBirthDate)) {
                    (*birthDate)[1] = newElementInt;
                } else {
                    cout << "Некорректно введенный месяц!" << endl;
                }
                break;
            case 3:
                cout << "Новый год: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                newElementInt = stoi(newElement);
                newBirthDate[2] = newElementInt;
                if (checkBirthDate(newBirthDate)) {
                    (*birthDate)[2] = newElementInt;
                } else {
                    cout << "Некорректно введенный год!" << endl;
                }
                break;
            default:
                cout << "Нет такой опции!" << endl;
                break;
        }
    }
}