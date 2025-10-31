#include "Methods.h"
#include "BookUnit.h"
#include "AllModuls.h"

using namespace std;

extern int PERSON_INDEX;


bool checkFullName(const string& element) {
    bool flag = true;
    flag *= isalpha(element[0]) && element.back() != '-';
    return flag;
}

bool checkEmail(const string& email) {
    // TODO: make this part
    return true;
}

bool checkPhoneNumber(const string& phoneNumber) {
    // TODO: make this part
    return true;
}

void deleteExtraSpace(string& element) {
    element.erase(element.begin(), find_if(element.begin(), element.end(), [](char c) {
        return c != ' ';
    }));
    element.erase(find_if(element.rbegin(), element.rend(), [](char c) {
        return c != ' ';
    }).base(), element.end());
}

void printBookUnits(const list<BookUnit>& units) {
    cout << "Вывод телефонного справочника: " << endl;
    cout << "ФИО //" << "Адресс //" << "Дата рождения //" << "Почта //" << "Телефонные номера" << endl;
    cout << "-----" << endl;
    // Сделал for-цикл, потому что CLion выдавал Clang-Tidy: "Use range-based for loop"
    for (const auto& iter : units) {
        iter.printBook();
        cout << "-----" << endl;
    }
    cout << "Вывод телефонного справочника завершён." << endl;
}

void createNewBook(list<BookUnit>& unit) {
    cout << "Имя, Фмлмия, email и телефонный номер обязательный к заполнению!" << endl;
    BookUnit newBook;
    // TODO: make this part
    PERSON_INDEX++;
}

void refactorBook(list<BookUnit>& unit) {
    // TODO: make this part
}

void deleteBook(list<BookUnit>& units) {
    if (units.empty()) {
        cout << "Телефонный справочник пуст!" << endl;
    }else {
        int numberToDelete;
        cout << "Введите номер строки, который желаете удалить: ";
        cin >> numberToDelete;
        numberToDelete--;

        if (PERSON_INDEX < numberToDelete || numberToDelete < 0) {
            cout << "Выход за переды телефонного справочника!" << endl;
        }
        else {
            auto iter = units.begin();
            advance(iter, numberToDelete);
            units.erase(iter);
            PERSON_INDEX--;
            cout << "Удаление строчки под номером " << numberToDelete << " заверешно!" << endl;
        }
    }
}
// придётся разбить на сортировки по каждому виду поля!
void sortData(list<BookUnit>& unit, int sortField) {
    // TODO: make this part
}