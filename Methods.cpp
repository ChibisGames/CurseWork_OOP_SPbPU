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
enum Field {
    FN1 = 1,
    FN2 = 2,
    FN3 = 3,
    ADDRESS1 = 4,
    ADDRESS2 = 5,
    ADDRESS3 = 6,
    ADDRESS4 = 7,
    ADDRESS5 = 8,
    ADDRESS6 = 9,
    ADDRESS7 = 10,
    BD1 = 11,
    BD2 = 12,
    BD3 = 13,
    E = 14,
    PN = 15
};

int mainMenu(int& opt) {
    auto bookUnits = new list<BookUnit>(MAX_UNITS);
    while (true) {
        cout << "Введите номер нужной опции: " << endl;
        cout << "1: Просмотреть телефонный справочник" << endl;
        cout << "2: Создать контакт" << endl;
        cout << "3: Редактировать контакт" << endl;
        cout << "4: Удалить контакт" << endl;
        cout << "5: Сортировать телефонный справочник" << endl;
        cout << "6: Найти контакт" << endl;
        cout << "7: Чтение из файла телефонного справочника" << endl;
        cout << "8: Записать телефонный справочник в файл" << endl;
        cout << "9: Выход из программы" << endl;
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
                sortData(*bookUnits);
                break;
            case 6:
                findData(*bookUnits);
                break;
            case 7:
                readFile(*bookUnits);
                break;
            case 8:
                writeFile(*bookUnits);
                break;

            case 9:
                cout << "Выход из системы" << endl;
                delete bookUnits;
                return 0;
            default:
                cout << "Нет такой опции!" << endl;
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
        correctData = checkEmail(email, newBook);
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
    BookUnit::toFormat(phoneNumber); // потому что toFormat статичный метод
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

void sortData(list<BookUnit>& units) {
    int opt = 0;
    while (true) {
        cout << "Выберите опции для поиска:" << endl;
        cout << "1: Сортировать по имени" << endl;
        cout << "2: Сортировать по фамилии" << endl;
        cout << "3: Сортировать по отчеству" << endl;
        cout << "4: Сортировать по стране" << endl;
        cout << "5: Сортировать по региону" << endl;
        cout << "6: Сортировать по городу" << endl;
        cout << "7: Сортировать по улицу" << endl;
        cout << "8: Сортировать по дом" << endl;
        cout << "9: Сортировать по корпус" << endl;
        cout << "10: Сортировать по квартира" << endl;
        cout << "11: Сортировать по дню рождения" << endl;
        cout << "12: Сортировать по месяцу рождения" << endl;
        cout << "13: Сортировать по году рождения" << endl;
        cout << "14: Сортировать по email" << endl;
        cout << "15: Сортировать по телефону" << endl;
        cout << "16: Выйти из опции" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        if (1 <= opt && opt <= 16) {
            break;
        }
    }

    switch (opt) {
        case FN1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getFullName())[0] < (*b.getFullName())[0];
            });
            break;
        case FN2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getFullName())[1] < (*b.getFullName())[1];
            });
            break;
        case FN3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getFullName())[2] < (*b.getFullName())[2];
            });
            break;

        case ADDRESS1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[0] < (*b.getAddress())[0];
            });
            break;
        case ADDRESS2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[1] < (*b.getAddress())[1];
            });
            break;
        case ADDRESS3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[2] < (*b.getAddress())[2];
            });
            break;
        case ADDRESS4:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[3] < (*b.getAddress())[3];
            });
            break;
        case ADDRESS5:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[4] < (*b.getAddress())[4];
            });
            break;
        case ADDRESS6:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[5] < (*b.getAddress())[5];
            });
            break;
        case ADDRESS7:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getAddress())[6] < (*b.getAddress())[6];
            });
            break;

        case BD1:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getBirthDate())[0] < (*b.getBirthDate())[0];
            });
            break;
        case BD2:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getBirthDate())[1] < (*b.getBirthDate())[1];
            });
            break;
        case BD3:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getBirthDate())[2] < (*b.getBirthDate())[2];
            });
            break;

        case E:
            units.sort([](BookUnit& a, BookUnit& b) {
                return (*a.getEmail()) < (*b.getEmail());
            });
            break;

        case PN:
            units.sort([](BookUnit& a, BookUnit& b) {
                a.sortPhoneNumbers();
                b.sortPhoneNumbers();
                const auto ai = a.getPhoneNumber()->begin();
                const auto bi = b.getPhoneNumber()->begin();
                return (*ai) < (*bi);
            });
            break;
        case 16:
            return;
        default:
            cout << "Нет такого поля!" << endl;
            break;
    }
}

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool isNumber(const string& str) {
    // Clion посоветовал исправить перебор for на all_of
    return all_of(str.begin(), str.end(), [](unsigned char c) {
        return isdigit(c);
    });
}

void findData(list<BookUnit>& units) {
    int opt = 0;
    string field;
    auto optData = vector<bool>(15);
    auto result = units;
    auto middleResult = list<BookUnit>(units.size());
    while (true) {
        cout << "Выберите опции для поиска:" << endl;
        if (!optData[0]) {cout << "1: Поиск по имени" << endl;}
        if (!optData[1]) {cout << "2: Поиск по фамилии" << endl;}
        if (!optData[2]) {cout << "3: Поиск по отчеству" << endl;}
        if (!optData[3]) {cout << "4: Поиск по стране" << endl;}
        if (!optData[4]) {cout << "5: Поиск по региону" << endl;}
        if (!optData[5]) {cout << "6: Поиск по городу" << endl;}
        if (!optData[6]) {cout << "7: Поиск по улицу" << endl;}
        if (!optData[7]) {cout << "8: Поиск по дом" << endl;}
        if (!optData[8]) {cout << "9: Поиск по корпус" << endl;}
        if (!optData[9]) {cout << "10: Поиск по квартира" << endl;}
        if (!optData[10]) {cout << "11: Поиск по дню рождения" << endl;}
        if (!optData[11]) {cout << "12: Поиск по месяцу рождения" << endl;}
        if (!optData[12]) {cout << "13: Поиск по году рождения" << endl;}
        if (!optData[13]) {cout << "14: Поиск по email" << endl;}
        if (!optData[14]) {cout << "15: Поиск по телефону" << endl;}
        cout << "16: Просмотреть искомые списки" << endl;
        cout << "17: Очистить поисковой фильтр" << endl;
        cout << "18: Выйти из опции" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        if (opt < 1 || opt > 18) {cout << "Нет такой опции!" << endl; continue;}
        if (1 <= opt && opt <= 10 ||  14 <= opt && opt <= 15) {
            cout << "Введите искомое значение: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> field;
            field = toLower(field);
        }
        if (11 <= opt && opt <= 13) {
            while (true) {
                cout << "Введите искомое значение: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> field;
                if (isNumber(field)) {
                    break;
                }else {
                    cout << "Это должно быть число!" << endl;
                }
            }
        }

        switch (opt) {
            case FN1:
                for (auto& unit : result) {
                    if (toLower((*unit.getFullName())[0]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[0] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case FN2:
                for (auto& unit : result) {
                    if (toLower((*unit.getFullName())[1]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[1] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case FN3:
                for (auto& unit : result) {
                    if (toLower((*unit.getFullName())[2]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[2] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;

            case ADDRESS1:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[0]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[3] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS2:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[1]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[4] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS3:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[2]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[5] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS4:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[3]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[6] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS5:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[4]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[7] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS6:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[5]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[8] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case ADDRESS7:
                for (auto& unit : result) {
                    if (toLower((*unit.getAddress())[6]) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[9] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;

            case BD1:
                for (auto& unit : result) {
                    if ((*unit.getBirthDate())[0] == stoi(field)) {
                        middleResult.push_back(unit);
                    }
                }
                optData[10] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case BD2:
                for (auto& unit : result) {
                    if ((*unit.getBirthDate())[1] == stoi(field)) {
                        middleResult.push_back(unit);
                    }
                }
                optData[11] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;
            case BD3:
                for (auto& unit : result) {
                    if ((*unit.getBirthDate())[2] == stoi(field)) {
                        middleResult.push_back(unit);
                    }
                }
                optData[12] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;

            case E:
                for (auto& unit : result) {
                    if (toLower((*unit.getEmail())) == field) {
                        middleResult.push_back(unit);
                    }
                }
                optData[13] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;

            case PN:
                for (auto& unit : result) {
                    for (auto iter = unit.getPhoneNumber()->begin();
                        iter != unit.getPhoneNumber()->end(); ++iter) {
                        if ((*iter) == field) {
                            middleResult.push_back(unit);
                            continue;
                        }
                    }
                }
                optData[14] = true;
                result.clear();
                result = middleResult;
                middleResult.clear();
                break;

            case 16:
                printBookUnits(result);
                break;

            case 17:
                result.clear();
                result = units;
                for (auto && iter : optData) {
                    iter = false;
                }
                break;

            case 18:
                return;
                //break;

            default:
                cout << "Нет такой опции!" << endl;
                break;
        }
    }
}

void readFile(list<BookUnit>& units) {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        cout << "Нет такой опции!" << endl;
        return;
    }

    units.clear();

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            BookUnit unit;
            unit.fromString(line);
            units.push_back(unit);
            PERSON_INDEX++;
        }
    }

    file.close();
    cout << "Чтение завершено!" << endl;

}

void writeFile(const list<BookUnit>& units) {
    ofstream file("data.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        cout << "Нет такой опции!" << endl;
        return;
    }

    for (const auto& unit : units) {
        file << unit.toString() << endl;
    }

    file.close();
    cout << "Запись завершена!" << endl;
}
