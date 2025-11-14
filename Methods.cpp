#include "AllModuls.h"
#include "Methods.h"
#include "BookUnit.h"
#include "FullName.h"
#include "Address.h"
#include "BirthDate.h"
#include "Email.h"
#include "PhoneNumbers.h"



using namespace std;


int MAX_UNITS = 50;
int PERSON_INDEX = 0;
enum SortField {
    SORT_BY_FN1 = 1,
    SORT_BY_FN2 = 2,
    SORT_BY_FN3 = 3,
    SORT_BY_ADDRESS1 = 4,
    SORT_BY_ADDRESS2 = 5,
    SORT_BY_ADDRESS3 = 6,
    SORT_BY_ADDRESS4 = 7,
    SORT_BY_ADDRESS5 = 8,
    SORT_BY_ADDRESS6 = 9,
    SORT_BY_ADDRESS7 = 10,
    SORT_BY_BD1 = 11,
    SORT_BY_BD2 = 12,
    SORT_BY_BD3 = 13,
    SORT_BY_E = 14,
    SORT_BY_PN = 15
};

int mainManu(int& opt) {
    auto bookUnits = new list<BookUnit>(MAX_UNITS);
    while (true) {
        cout << "Введите номер нужной опции: " << endl;
        cout << "1: Просмотреть телефонный справочник" << endl;
        cout << "2: Создать контакт" << endl;
        cout << "3: Редактировать контакт" << endl;
        cout << "4: Удалить аккаунт" << endl;
        cout << "5: Выход из программы" << endl;
        cout << "Номер опции: ";
        cin >> opt;
        switch (opt) {
            case 1:
                printBookUnits(*bookUnits);
                break;
            case 2:
                createNewBook(*bookUnits);
                break;
            case 3:
                refactorBook(*bookUnits);
                break;
            case 4:
                deleteBook(*bookUnits);
                break;
            case 5:
                cout << "Выход из системы" << endl;
                delete bookUnits;
                return 0;
            default:
                cout << "Нет такой опции!";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printBookUnits(const list<BookUnit>& units) {
    cout << "Вывод телефонного справочника: " << endl;
    cout << "ФИО //" << "Адрес //" << "Дата рождения //" << "Почта //" << "Телефонные номера" << endl;
    cout << "-----" << endl;
    // Сделал for-цикл, потому что CLion выдавал Clang-Tidy: "Use range-based for loop"
    for (const auto& iter : units) {
        if (!iter.isEmpty()) {
            iter.printBook();
            cout << "-----" << endl;
        }
    }
    cout << "Вывод телефонного справочника завершён." << endl;
}

void createNewBook(list<BookUnit>& units) {
    BookUnit newBook;
    cout << "Имя, Фамилия, email и телефонный номер обязательный к заполнению!" << endl;
    bool correctData = false;
    auto fullName = vector<string>(3);
    while (!correctData) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "=== Ввод ФИО ===" << endl;
        cout << "Введите имя: ";
        cin >> fullName[0];
        cout << "Введите фамилию: ";
        cin >> fullName[1];
        cout << "Введите отчество: ";
        cin >> fullName[2];
        correctData = checkFullName(fullName);
        if (!correctData){cout << "Некорректность вводимых ФИО! Повторите ввод!" << endl;}
    }
    newBook.addOrChangeFullName(fullName);

    cout << "=== Ввод адреса ===" << endl;
    auto address = vector<string>(7);
    cout << "Введите страну: ";
    cin >> address[0];
    cout << "Введите регион: ";
    cin >> address[1];
    cout << "Введите город: ";
    cin >> address[2];
    cout << "Введите улицу: ";
    cin >> address[3];
    cout << "Введите дом: ";
    cin >> address[4];
    cout << "Введите корпус: ";
    cin >> address[5];
    cout << "Введите квартиру: ";
    cin >> address[6];
    newBook.addOrChangeAddress(address);

    correctData = false;
    auto birthDate = vector<int>(3);
    while (!correctData) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "=== Ввод даты рождения ===" << endl;
        cout << "Введите день: ";
        cin >> birthDate[0];
        cout << "Введите месяц: ";
        cin >> birthDate[1];
        cout << "Введите год: ";
        cin >> birthDate[2];
        correctData = checkBirthDate(birthDate);
        if (!correctData){cout << "Некорректность вводимой даты рождения! Повторите ввод!" << endl;}
    }
    newBook.addOrChangeBirthDate(birthDate);

    correctData = false;
    string email;
    while (!correctData) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "=== Ввод email ===" << endl;
        cout << "Введите email: ";
        cin >> email;
        correctData = checkEmail(email);
        if (!correctData){cout << "Некорректность вводимого email! Повторите ввод!" << endl;}
    }
    newBook.addOrChangeEmail(email);

    correctData = false;
    string phoneNumber;
    while (!correctData) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "=== Ввод телефона ===" << endl;
        cout << "Введите телефон: ";
        cin >> phoneNumber;
        correctData = checkPhoneNumber(phoneNumber);
        if (!correctData){cout << "Некорректность вводимого телефона! Повторите ввод!" << endl;}
    }
    newBook.addPhoneNumber(phoneNumber);

    auto iter = units.begin();
    advance(iter, PERSON_INDEX);
    iter->createBook(newBook);

    PERSON_INDEX++;
}

void refactorBook(list<BookUnit>& units) {
    int opt = 0;
    auto unit = units.begin();
    while (opt != -1) {
        cout << "Выберите строчку, которую хотите изменить (0, если хотите отменить операцию):";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        opt--;
        if (0 <= opt && opt < PERSON_INDEX) {
            advance(unit, opt);
            break;
        } else if (opt != -1) {
            cout << "Нет такой строчки!" << endl;
        }
    }
    opt = 0;
    while (opt != 6) {
        cout << "1: Изменить ФИО" << endl;
        cout << "2: Изменить адрес" << endl;
        cout << "3: Изменить дату рождения" << endl;
        cout << "4: Изменить email" << endl;
        cout << "5: Изменить/добавить телефонный номер" << endl;
        cout << "6: Выйти из окна редактирования" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        switch (opt) {
            case 1:
                refactorFullName(*unit);
                break;
            case 2:
                refactorAddress(*unit);
                break;
            case 3:
                refactorBirthDate(*unit);
                break;
            case 4:
                refactorEmail(*unit);
                break;
            case 5:
                addAndRefactorPhoneNumber(*unit);
                break;
            default:
                cout << "Выход из окна редактирования" << endl;
                break;
        }
    }
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

        if (PERSON_INDEX <= numberToDelete || numberToDelete < 0) {
            cout << "Выход за пределы телефонного справочника!" << endl;
        }
        else {
            auto iter = units.begin();
            advance(iter, numberToDelete);
            units.erase(iter);
            PERSON_INDEX--;
            numberToDelete++;
            cout << "Удаление строчки под номером " << numberToDelete << " завершено!" << endl;
        }
    }
}

vector<BookUnit>& readFile() {}

void writeFile(list<BookUnit>& units) {}

// придётся разбить на сортировки по каждому виду поля!
void sortData(list<BookUnit>& units, int sortField) {
    switch (sortField) {
        case SORT_BY_FN1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getFullName()[0] < b.getFullName()[0];
            });
            break;
        case SORT_BY_FN2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getFullName()[1] < b.getFullName()[1];
            });
            break;
        case SORT_BY_FN3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getFullName()[2] < b.getFullName()[2];
            });
            break;

        case SORT_BY_ADDRESS1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[0] < b.getAddress()[0];
            });
            break;
        case SORT_BY_ADDRESS2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[1] < b.getAddress()[1];
            });
            break;
        case SORT_BY_ADDRESS3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[2] < b.getAddress()[2];
            });
            break;
        case SORT_BY_ADDRESS4:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[3] < b.getAddress()[3];
            });
            break;
        case SORT_BY_ADDRESS5:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[4] < b.getAddress()[4];
            });
            break;
        case SORT_BY_ADDRESS6:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[5] < b.getAddress()[5];
            });
            break;
        case SORT_BY_ADDRESS7:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getAddress()[6] < b.getAddress()[6];
            });
            break;

        case SORT_BY_BD1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getBirthDate()[0] < b.getBirthDate()[0];
            });
            break;
        case SORT_BY_BD2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getBirthDate()[1] < b.getBirthDate()[1];
            });
            break;
        case SORT_BY_BD3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getBirthDate()[2] < b.getBirthDate()[2];
            });
            break;

        case SORT_BY_E:
            units.sort([](BookUnit& a, BookUnit& b) {
                return a.getEmail() < b.getEmail();
            });
            break;

        case SORT_BY_PN:
            units.sort([](BookUnit& a, BookUnit& b) {
                a.sortPhoneNumbers();
                b.sortPhoneNumbers();
                return a.getPhoneNumber()[0] < b.getPhoneNumber()[0];
            });
            break;
        default:
            cout << "Нет такого поля!" << endl;
            break;
    }
}

void findData(list<BookUnit>& units, int findField) {
    // TODO: make this part
}