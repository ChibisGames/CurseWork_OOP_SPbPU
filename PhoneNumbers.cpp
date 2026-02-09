#include "AllModuls.h"
#include "PhoneNumbers.h"

using namespace std;


bool checkPhoneNumber(const string& phoneNumber) {
    const regex re(R"((\+7|8)(\d{10}|\(\d{3}\)\d{7}|\(\d{3}\)\d{3}-\d{2}-\d{2}))");
    return regex_match(phoneNumber, re);
}

void refactorPhoneNumber(BookUnit& unit) {
    int pos;
    unit.printPhoneNumbers();
    cout << "Выберите номер телефона, который хотите изменить: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> pos;
    pos--;
    if (0 <= pos && pos < unit.getPhoneNumberSize()) {
        string phoneNumber;
        cout << "Введите новый телефон: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> phoneNumber;
        if (checkPhoneNumber(phoneNumber) || phoneNumber == "-") {
            BookUnit::toFormat(phoneNumber); // потому что toFormat статичный метод
            unit.changePhoneNumber(phoneNumber, pos);
        }
    }else {
        cout << "Нет такого номера!" << endl;
    }
}

void addAndRefactorPhoneNumber(BookUnit& unit) {
    int opt;
    string number;
    while (true) {
        cout << "1: Добавить телефонный номер" << endl;
        cout << "2: Изменить телефонный номер (чтобы удалить ввести в опции '-')" << endl;
        cout << "3: Выйти из окна изменения телефонного номера" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        if (opt == 1) {
            cout << "Введите новый телефон: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> number;
            if (checkPhoneNumber(number)) {
                BookUnit::toFormat(number); // потому что toFormat статичный метод
                unit.addPhoneNumber(number);
            }
            else {
                cout << "Не корректный номер!" << endl;
            }
        } else if (opt == 2) {
            refactorPhoneNumber(unit);
        } else if (opt == 3) {
            break;
        } else {
            cout << "Нет такой опции!" << endl;
        }
    }
}