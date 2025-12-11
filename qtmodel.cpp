#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

#include "BookUnit.h"
#include "Methods.h"
#include "qtmodel.h"


extern int MAX_UNITS;
extern int PERSON_INDEX;


int qtMainMenu() {
    QApplication app();
    //QLabel *label = new QLabel("Hello World!");
    auto bookUnits = new list<BookUnit>(MAX_UNITS);

    auto *window = new QWidget;
    window->setWindowTitle("Phone Book");
    window->setMinimumWidth(800);


    auto *layout = new QHBoxLayout;
    window->setLayout(layout);

    auto *tableWidget = createQtTable(window);
    layout->addWidget(tableWidget);





    BookUnit testUnit;
    testUnit.fullName = {"Иванов", "Иван", "Иванович"};
    testUnit.address = {"Россия", "Москва", "ул. Ленина", "д. 10", "кв. 5"};
    testUnit.birthDate = {15, 5, 1990};
    testUnit.email = "ivanov@mail.ru";
    testUnit.phoneNumber = {"+7(999)123-45-67", "+7(495)765-43-21"};

    addBookUnitToTable(tableWidget, testUnit, 0);

    // Добавим еще один пример
    BookUnit testUnit2;
    testUnit2.fullName = {"Петрова", "Мария", "Сергеевна"};
    testUnit2.address = {"Россия", "Санкт-Петербург", "Невский пр.", "д. 25"};
    testUnit2.birthDate = {3, 11, 1985};
    testUnit2.email = "petrova@gmail.com";
    testUnit2.phoneNumber = {"+7(812)333-44-55"};

    addBookUnitToTable(tableWidget, testUnit2, 1);

    BookUnit testUnit3;
    testUnit3.fullName = {"Петрова", "Мария", "Сергеевна"};
    testUnit3.address = {"Россия", "Санкт-Петербург", "Невский пр.", "д. 25"};
    testUnit3.birthDate = {3, 11, 1985};
    testUnit3.email = "petrova@gmail.com";
    testUnit3.phoneNumber = {"+7(812)333-44-55"};

    addBookUnitToTable(tableWidget, testUnit3, 2);


    //label->show();
    window->show();
}

QTableWidget* createQtTable(QWidget *window) {
    QStringList headers = {"ФИО", "Адрес", "День рождения", "Email", "Телефон"};
    auto *tableWidget = new QTableWidget;

    tableWidget->setColumnCount(headers.count());
    tableWidget->setHorizontalHeaderLabels(headers);

    // Устанавливаем разные режимы для разных столбцов
    QHeaderView* header = tableWidget->horizontalHeader();

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ФИО - растягивается
    header->setSectionResizeMode(1, QHeaderView::Stretch); // Адрес - растягивается

    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Дата рождения - фиксированный

    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Email
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Телефон

    // Устанавливаем начальные размеры
    tableWidget->setColumnWidth(3, 100);   // Дата рождения
    tableWidget->setColumnWidth(4, 100);   // Email
    tableWidget->setColumnWidth(5, 150);   // Телефон

    // Для растягивающихся столбцов можно установить минимальную ширину
    tableWidget->horizontalHeader()->setMinimumSectionSize(100);

    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    return tableWidget;
}

// Функция для добавления BookUnit в таблицу
void addBookUnitToTable(QTableWidget* tableWidget, const BookUnit& bookUnit, int row) {
    // Увеличиваем количество строк в таблице
    tableWidget->insertRow(row);

    // ФИО - объединяем из вектора
    QString fullNameStr;
    for (const auto& namePart : bookUnit.fullName) {
        if (!namePart.empty()) {
            if (!fullNameStr.isEmpty()) fullNameStr += " ";
            fullNameStr += QString::fromStdString(namePart);
        }
    }
    tableWidget->setItem(row, 0, new QTableWidgetItem(fullNameStr));

    // Адрес - объединяем из вектора
    QString addressStr;
    for (const auto& addrPart : bookUnit.address) {
        if (!addrPart.empty()) {
            if (!addressStr.isEmpty()) addressStr += ", ";
            addressStr += QString::fromStdString(addrPart);
        }
    }
    tableWidget->setItem(row, 1, new QTableWidgetItem(addressStr));

    // Дата рождения - форматируем из вектора
    QString birthDateStr;
    if (bookUnit.birthDate.size() >= 3) {
        birthDateStr = QString("%1.%2.%3")
        .arg(bookUnit.birthDate[0], 2, 10, QChar('0'))
            .arg(bookUnit.birthDate[1], 2, 10, QChar('0'))
            .arg(bookUnit.birthDate[2]);
    }
    tableWidget->setItem(row, 2, new QTableWidgetItem(birthDateStr));

    // Email
    tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(bookUnit.email)));

    // Телефоны - объединяем из списка
    QString phoneStr;
    for (const auto& phone : bookUnit.phoneNumber) {
        if (!phone.empty()) {
            if (!phoneStr.isEmpty()) phoneStr += ",\n";
            phoneStr += QString::fromStdString(phone);
        }
    }
    tableWidget->setItem(row, 4, new QTableWidgetItem(phoneStr));

    tableWidget->resizeRowToContents(row);

    tableWidget->setRowHeight(row, tableWidget->rowHeight(row) + 10);
}

void updateQtTable (QTableWidget *tableWidget) {

}
