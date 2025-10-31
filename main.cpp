#include "BookUnit.h"
#include "AllModuls.h"
#include "Methods.h"

using namespace std;


int MAX_UNITS = 50;
int PERSON_INDEX = 0;

int menu(int& opt) {
    auto bookUnits = new list<BookUnit>[MAX_UNITS];
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
                delete[] bookUnits;
                return 0;
            default:
                cout << "Нет такой опции!";
        }
    }
}


int main() {
    int opt = 0;
    menu(opt);
    return 0;

}

