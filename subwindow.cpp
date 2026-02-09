#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include "FullName.h"
#include "BirthDate.h"
#include "Email.h"
#include "PhoneNumbers.h"
#include "subwindow.h"

SubWindow::SubWindow(WindowMode mode, QTableWidget *tableWidget, list<BookUnit> *bookUnits, QWidget *parent) : QDialog(parent),
    newTableWidget(tableWidget), mode(mode), bookUnits(bookUnits)
{
    setupSubWindow();
}

// Выбор окна действия
void SubWindow::setupSubWindow(){
    if (mode == WindowMode::Add) setupAddWindow();
    else if (mode == WindowMode::Refactor) setupRefactorWindow();
    else if (mode == WindowMode::Delete) setupDeleteWindow();

}

// Окно для создания нового контакта
void SubWindow::setupAddWindow(){
    setMinimumSize(300, 500);
    auto mainLayout = new QVBoxLayout(this);

    // Поле для ФИО
    auto name = new QHBoxLayout();
    nameEdit = new QLineEdit(this);
    name->addWidget(new QLabel("Имя:", this));
    name->addWidget(nameEdit);

    auto surname = new QHBoxLayout();
    surnameEdit = new QLineEdit(this);
    surname->addWidget(new QLabel("Фамилия:", this));
    surname->addWidget(surnameEdit);

    auto patronymic = new QHBoxLayout();
    patronymicEdit = new QLineEdit(this);
    patronymic->addWidget(new QLabel("Отчество:", this));
    patronymic->addWidget(patronymicEdit);

    // Адрес
    auto country = new QHBoxLayout();
    countryEdit = new QLineEdit(this);
    country->addWidget(new QLabel("Страна:", this));
    country->addWidget(countryEdit);

    auto region = new QHBoxLayout();
    regionEdit = new QLineEdit(this);
    region->addWidget(new QLabel("Регион:", this));
    region->addWidget(regionEdit);

    auto city = new QHBoxLayout();
    cityEdit = new QLineEdit(this);
    city->addWidget(new QLabel("Город:", this));
    city->addWidget(cityEdit);

    auto street = new QHBoxLayout();
    streetEdit = new QLineEdit(this);
    street->addWidget(new QLabel("Улица:", this));
    street->addWidget(streetEdit);

    auto home = new QHBoxLayout();
    homeEdit = new QLineEdit(this);
    home->addWidget(new QLabel("Дом:", this));
    home->addWidget(homeEdit);

    auto corpus = new QHBoxLayout();
    corpusEdit = new QLineEdit(this);
    corpus->addWidget(new QLabel("Корпус:", this));
    corpus->addWidget(corpusEdit);

    auto flat = new QHBoxLayout();
    flatEdit = new QLineEdit(this);
    flat->addWidget(new QLabel("Квартира:", this));
    flat->addWidget(flatEdit);

    // Дата рождения
    auto date = new QHBoxLayout();
    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true); // выпадающий календарь
    dateEdit->setDisplayFormat("dd.MM.yyyy"); // формат
    dateEdit->setMaximumDate(QDate::currentDate().addDays(-1)); // вчера последний день
    dateEdit->setDate(QDate::currentDate().addDays(-1)); // вчера по умолчанию
    date->addWidget(new QLabel("Дата рождения:", this));
    date->addWidget(dateEdit);

    // Email
    auto email = new QHBoxLayout();
    emailEdit = new QLineEdit(this);
    email->addWidget(new QLabel("Email:", this));
    email->addWidget(emailEdit);

    // Телефонный номер
    auto phoneNumber = new QHBoxLayout();
    phoneNumberEdit = new QLineEdit(this);
    phoneNumber->addWidget(new QLabel("Телефонный номер:", this));
    phoneNumber->addWidget(phoneNumberEdit);


    acceptButtun = new QPushButton("Принять", this);
    connect(acceptButtun, &QPushButton::clicked, this, &SubWindow::acceptAdd);

    cancelButton = new QPushButton("Отменить", this);
    connect(cancelButton, &QPushButton::clicked, this, &SubWindow::cancelEdit);

    // добавляем всё в главный слой
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButtun);

    mainLayout->addLayout(name);
    mainLayout->addLayout(surname);
    mainLayout->addLayout(patronymic);

    mainLayout->addLayout(country);
    mainLayout->addLayout(region);
    mainLayout->addLayout(city);
    mainLayout->addLayout(street);
    mainLayout->addLayout(home);
    mainLayout->addLayout(corpus);
    mainLayout->addLayout(flat);

    mainLayout->addLayout(date);

    mainLayout->addLayout(email);

    mainLayout->addLayout(phoneNumber);

    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

}

// создание окна изменений
void SubWindow::setupRefactorWindow(){
    setMinimumSize(300, 250);
    auto mainLayout = new QVBoxLayout(this);

    cancelButton = new QPushButton("Отменить", this);
    connect(cancelButton, &QPushButton::clicked, this, &SubWindow::cancelEdit);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);


    if (newTableWidget->rowCount() == 0) { // нет контактов
        mainLayout->addWidget(new QLabel("Нет контактов для изменения", this));
    }else{
        mainLayout->addWidget(new QLabel("Выберите, какую строку изменить", this));

        spinBox = new QSpinBox(this);
        slider = new QSlider(Qt::Horizontal, this);

        spinBox->setRange(1, newTableWidget->rowCount());
        slider->setRange(1, newTableWidget->rowCount());


        QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        auto layout = new QHBoxLayout();
        layout->addWidget(slider);
        layout->addWidget(spinBox);
        mainLayout->addLayout(layout);


        refactorItemCombo = new QComboBox(this); // создаём выпадающий список
        refactorItemCombo->addItem("Добавить телефон", 0);

        refactorItemCombo->addItem("Изменить имя", 1);
        refactorItemCombo->addItem("Изменить фимилию", 2);
        refactorItemCombo->addItem("Изменить Отчетсво", 3);

        refactorItemCombo->addItem("Изменить страну", 4);
        refactorItemCombo->addItem("Изменить регион", 5);
        refactorItemCombo->addItem("Изменить город", 6);
        refactorItemCombo->addItem("Изменить улицу", 7);
        refactorItemCombo->addItem("Изменить дом", 8);
        refactorItemCombo->addItem("Изменить корпус", 9);
        refactorItemCombo->addItem("Изменить квартиру", 10);

        refactorItemCombo->addItem("Изменить день рождения", 11);
        refactorItemCombo->addItem("Изменить месяц рождения", 12);
        refactorItemCombo->addItem("Изменить год рождения", 13);


        refactorItemCombo->addItem("Изменить email", 14);

        refactorItemCombo->addItem("Изменить телефон ('-' - удалить)", 15);

        mainLayout->addWidget(refactorItemCombo);


        auto newItem = new QHBoxLayout();
        newItem->addWidget(new QLabel("Новое значение:", this));
        refactorItemLine = new QLineEdit(this);
        newItem->addWidget(refactorItemLine);
        mainLayout->addLayout(newItem);

        auto newEmail = new QHBoxLayout();
        newEmail->addWidget(new QLabel("Новый email (только при изменении имени!):", this));
        newEmailEdit = new QLineEdit(this);
        newEmail->addWidget(newEmailEdit);
        mainLayout->addLayout(newEmail);

        auto phoneIndex = new QHBoxLayout(); // Нет сил делать через ?ивенты?
        phoneIndex->addWidget(new QLabel("Номер телефона в списке (если изменяете его):", this));
        refactorPhoneNumberIndex = new QSpinBox(this);
        refactorPhoneNumberIndex->setMinimum(1);
        phoneIndex->addWidget(refactorPhoneNumberIndex);
        mainLayout->addLayout(phoneIndex);


        acceptButtun = new QPushButton("Принять", this);
        acceptButtun->setDefault(true);
        connect(acceptButtun, &QPushButton::clicked, this, &SubWindow::acceptRefactor);

        buttonLayout->addWidget(acceptButtun);
    }
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

void SubWindow::setupDeleteWindow() {
    setMinimumSize(300, 100);
    auto mainLayout = new QVBoxLayout(this);

    cancelButton = new QPushButton("Отменить", this);
    connect(cancelButton, &QPushButton::clicked, this, &SubWindow::cancelEdit);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);


    if (newTableWidget->rowCount() == 0) { // нет контактов
        mainLayout->addWidget(new QLabel("Нет контактов на удаление", this));
    }else{
        mainLayout->addWidget(new QLabel("Выберите, какую строку удалить", this));

        spinBox = new QSpinBox(this);
        slider = new QSlider(Qt::Horizontal, this);

        spinBox->setRange(1, newTableWidget->rowCount());
        slider->setRange(1, newTableWidget->rowCount());


        QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        auto layout = new QHBoxLayout();
        layout->addWidget(slider);
        layout->addWidget(spinBox);
        mainLayout->addLayout(layout);

        acceptButtun = new QPushButton("Принять", this);
        acceptButtun->setDefault(true);
        connect(acceptButtun, &QPushButton::clicked, this, &SubWindow::acceptDelete);

        buttonLayout->addWidget(acceptButtun);
    }
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

bool SubWindow::doAccept(){
    bool flag = true;
    auto name = nameEdit->text().toStdString();
    auto email = emailEdit->text().toStdString();

    flag *= checkNameElement(name);
    flag *= checkNameElement(surnameEdit->text().toStdString());
    flag *= checkNameElement(patronymicEdit->text().toStdString());

    flag *= checkBirthDate(getDateEdit()); // Должно всегда проходить (так задаётся календарём)

    flag *= checkEmail(email, name);
    flag *= checkPhoneNumber(phoneNumberEdit->text().toStdString());


    return flag;
}

bool SubWindow::doRefactor() {
    int newIndex = refactorItemCombo->currentData().toInt();

    auto newItem = refactorItemLine->text().toStdString();
    auto it = bookUnits->begin();
    advance(it, spinBox->value() - 1);
    auto newBirthDate = it->getBirthDate();

    auto name = newEmailEdit->text().toStdString(); // Для измнении имени + почты

    if (newIndex == 0) return checkPhoneNumber(newItem);
    if (newIndex == 1)
        return checkNameElement(newItem) && checkEmail(name, newItem);
    if (2 <= newIndex && newIndex <= 3) return checkNameElement(newItem);
    if (4 <= newIndex && newIndex <= 10) return true;

    if (newIndex == 11){
        (*newBirthDate)[0] = refactorItemLine->text().toInt();
        return checkBirthDate(*newBirthDate);
    }
    if (newIndex == 12){
        (*newBirthDate)[1] = refactorItemLine->text().toInt();
        return checkBirthDate(*newBirthDate);
    }
    if (newIndex == 13){
        (*newBirthDate)[2] = refactorItemLine->text().toInt();
        return checkBirthDate(*newBirthDate);
    }
    if (newIndex == 14) return checkEmail(newItem, *it);
    if (newIndex == 15){
        auto phoneNumberIndex = refactorPhoneNumberIndex->value();
        return ((newItem == "-") || checkPhoneNumber(newItem)) * \
               (1 <= phoneNumberIndex && phoneNumberIndex <= (int)it->getPhoneNumberSize());
    }
    return false;

}

// слот для кнопки принять при создании контакта
void SubWindow::acceptAdd() {
    if (doAccept()){
        emit accept();
    }else{
        QMessageBox::information(this, "Некорректный ввод", "Вы ввели некорректную информацию!");
        return;
    }
}

// слот для кнопки принять при изменении контакта
void SubWindow::acceptRefactor() {
    // изменить?
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите изменить выбранный контакт?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    if (doRefactor()){
        emit accept();
    }else{
        QMessageBox::information(this, "Некорректный ввод", "Вы ввели некорректную информацию!");
        return;
    }
}

// слот для кнопки принять при удалении контакта
void SubWindow::acceptDelete() {
    // удалить?
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите удалить выбранный контакт?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }
    emit accept();
}

// слот кнопки отмены
void SubWindow::cancelEdit() {
    emit reject();
}

// ДАЛЬШЕ ГЕТЕРЫ
int SubWindow::getRow(){
    return spinBox->value();
}

int SubWindow::getRefactorItemIndex(){
    return refactorItemCombo->currentData().toInt();
}

QString SubWindow::getRefactorLine(){
    return refactorItemLine->text();
}

QString SubWindow::getNewEmailLine(){
    return newEmailEdit->text();
}


vector<std::string> SubWindow::getFullName(){
    auto fullName = vector<std::string>(3);
    fullName[0] = nameEdit->text().toStdString();
    fullName[1] = surnameEdit->text().toStdString();
    fullName[2] = patronymicEdit->text().toStdString();
    return fullName;
}

vector<std::string> SubWindow::getAddress(){
    auto address = vector<std::string>(7);
    address[0] = countryEdit->text().toStdString();
    address[1] = regionEdit->text().toStdString();
    address[2] = cityEdit->text().toStdString();
    address[3] = streetEdit->text().toStdString();
    address[4] = homeEdit->text().toStdString();
    address[5] = corpusEdit->text().toStdString();
    address[6] = flatEdit->text().toStdString();
    return address;
}

vector<int> SubWindow::getDateEdit(){
    auto date = vector<int>(3);
    date[0] = dateEdit->date().day();
    date[1] = dateEdit->date().month();
    date[2] = dateEdit->date().year();
    return date;
}

std::string SubWindow::getEmail(){
    return emailEdit->text().toStdString();
}

std::string SubWindow::getPhoneNumber(){
    auto str = phoneNumberEdit->text().toStdString();
    BookUnit::toFormat(str);
    return str;
}

int SubWindow::getRefactorPhoneNumberIndex(){
    return refactorPhoneNumberIndex->value() - 1;
}
