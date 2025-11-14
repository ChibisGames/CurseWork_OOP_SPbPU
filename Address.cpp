#include "AllModuls.h"
#include "Address.h"
#include "BookUnit.h"

using namespace std;


void refactorAddress(BookUnit& unit) {
    int opt = 0;
    auto address = unit.getAddress();
    string newElement;
    while (opt != 8) {
        cout << "1: Изменить страну" << endl;
        cout << "2: Изменить регион" << endl;
        cout << "3: Изменить город" << endl;
        cout << "4: Изменить улицу" << endl;
        cout << "5: Изменить дом" << endl;
        cout << "6: Изменить корпус" << endl;
        cout << "7: Изменить квартиру" << endl;
        cout << "8: Выйти из окна изменения ФИО" << endl;
        cout << "Номер опции: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "Новая страна: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[0] = newElement;
                break;
            case 2:
                cout << "Новый регион: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[1] = newElement;
                break;
            case 3:
                cout << "Новый город: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[2] = newElement;
                break;
            case 4:
                cout << "Новая улица: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[3] = newElement;
                break;
            case 5:
                cout << "Новый дом: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[4] = newElement;
                break;
            case 6:
                cout << "Новый корпус: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[5] = newElement;
                break;
            case 7:
                cout << "Новая квартира: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newElement;
                (*address)[6] = newElement;
                break;
            default:
                cout << "Выход в меню редактировании ФИО" << endl;
                break;
        }
    }
}