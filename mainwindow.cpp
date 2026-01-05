#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "BookUnit.h"
#include "subwindow.h"
#include "database.h"

// настройка главного окна
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    bookUnits = new list<BookUnit>(MAX_UNITS); // создаём массив клиентов
    //(*bookUnits).resize(MAX_UNITS); // Эта строчка чуть не заруинило всю курсовую
    setupMainWindow(); // запускаем поднастройку главного окна
    setWindowTitle("Телефонный справочник"); // название главного окна
    setMinimumSize(800, 600); // минимальные требования главного окна
}

// начало процесса работы
void MainWindow::setupMainWindow()
{
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    createTable(); // Создаём таблицу


    findBlock = new FindAndSortWidget(tableWidget, this); // Создаём поле поиска
    findBlock->setMinimumHeight(65); // Чтобы статус виден был

    mainLayout->addWidget(findBlock); // Поиск первй
    mainLayout->addWidget(tableWidget); // за ним таблица

    // Панель с кнопками
    //subWindow = new SubWindow(tableWidget, this); // Создаём добавление/редактирование/удаление
    setupButtons();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(refactorButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonLayout); // кнопки "непоиска" в конце
}

// создание и настройка таблицы
void MainWindow::createTable()
{
    QStringList headers = {"ФИО", "Адрес", "День рождения", "Email", "Телефон"};
    tableWidget = new QTableWidget(this); // креэйт таблицу
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отрубаю редактирование таблицы ручками

    tableWidget->setColumnCount(headers.count()); // устанавливаем кол-во колонок
    tableWidget->setHorizontalHeaderLabels(headers); // называем их

    QHeaderView* header = tableWidget->horizontalHeader(); // разные режимы для разных столбцов


    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ФИО
    header->setSectionResizeMode(1, QHeaderView::Stretch); // Адрес
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Дата рождения
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Email
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Телефон

    tableWidget->horizontalHeader()->setMinimumSectionSize(100); // Начальные размеры (На всяк-провсяк)
}

// установка кнопок внизу экрана
void MainWindow::setupButtons()
{
    // кнопка создание контакта
    addButton = new QPushButton("Добавить", this);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addBook);

    // кнопка редактирования контакта
    refactorButton = new QPushButton("Редактировать", this);
    connect(refactorButton, &QPushButton::clicked, this, &MainWindow::refactorBook);

    // кнопка удаления контакта
    deleteButton = new QPushButton("Удалить", this);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteBook);

    loadButton = new QPushButton("Загрузить", this); // кнопка загрузки из файла
    saveButton = new QPushButton("Сохранить", this); // кнопка сохранения в файл

    loadButton->setMinimumHeight(30);
    saveButton->setMinimumHeight(30);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadData); // конектим функцию загрузки
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveData); // конектим функцию сохранения
}

// добавление контакта в таблицу
void MainWindow::addBookUnitToTable(BookUnit& bookUnit, int row)
{
    tableWidget->insertRow(row);

    // ФИО - объединяем из вектора
    QString fullNameStr;
    for (const auto& namePart : *bookUnit.getFullName()) {
        if (!namePart.empty()) {
            if (!fullNameStr.isEmpty()) fullNameStr += " ";
            fullNameStr += QString::fromStdString(namePart);
        }
    }
    tableWidget->setItem(row, 0, new QTableWidgetItem(fullNameStr));

    // Адрес - объединяем из вектора
    QString addressStr;
    for (const auto& addrPart : *bookUnit.getAddress()) {
        if (!addrPart.empty()) {
            if (!addressStr.isEmpty()) addressStr += ", ";
            addressStr += QString::fromStdString(addrPart);
        }
    }
    tableWidget->setItem(row, 1, new QTableWidgetItem(addressStr));

    // Дата рождения - форматируем из вектора
    QString birthDateStr;
    if ((*bookUnit.getBirthDate()).size() >= 3) {
        birthDateStr = QString("%1.%2.%3")
        .arg((*bookUnit.getBirthDate())[0], 2, 10, QChar('0'))
            .arg((*bookUnit.getBirthDate())[1], 2, 10, QChar('0'))
            .arg((*bookUnit.getBirthDate())[2]);
    }
    tableWidget->setItem(row, 2, new QTableWidgetItem(birthDateStr));

    // Email
    tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(*bookUnit.getEmail())));

    // Телефоны - объединяем из списка
    QString phoneStr;
    for (const auto& phone : *bookUnit.getPhoneNumber()) {
        if (!phone.empty()) {
            if (!phoneStr.isEmpty()) phoneStr += ",\n";
            phoneStr += QString::fromStdString(phone);
        }
    }
    tableWidget->setItem(row, 4, new QTableWidgetItem(phoneStr));

    tableWidget->resizeRowToContents(row);
    tableWidget->setRowHeight(row, tableWidget->rowHeight(row) + 10);
}

// Обновление таблицы
void MainWindow::updateTable()
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    for (auto &unit : *bookUnits) {
        if (!unit.isEmpty()) addBookUnitToTable(unit, tableWidget->rowCount());
    }
}

// слот для кнопки
void MainWindow::addBook() {
    auto *subWindow = new SubWindow(WindowMode::Add, tableWidget, bookUnits, this);

    connect(subWindow, &SubWindow::accepted, this, [this, subWindow]() {
        BookUnit newBook;
        newBook.addOrChangeFullName(subWindow->getFullName());
        newBook.addOrChangeAddress(subWindow->getAddress());
        newBook.addOrChangeBirthDate(subWindow->getDateEdit());
        newBook.addOrChangeEmail(subWindow->getEmail());
        newBook.addPhoneNumber(subWindow->getPhoneNumber());

        //auto iter = bookUnits->begin();
        //advance(iter, tableWidget->rowCount());
        //iter->createBook(newBook); // на этой строчки вылетает - не понял почему (добавление именно после загрузки файла)
        bookUnits->push_back(newBook);
        personIndex++;

        updateTable();
    });

    subWindow->exec(); // открытие окна добавления
    subWindow->deleteLater(); // безопасное удаление окна
}

// слот для кнопки
void MainWindow::refactorBook() {
    auto *subWindow = new SubWindow(WindowMode::Refactor, tableWidget, bookUnits, this);

    connect(subWindow, &SubWindow::accepted, this, [this, subWindow]() {

        auto iter = bookUnits->begin();
        advance(iter, subWindow->getRow() - 1);

        int refactorItemIndex = subWindow->getRefactorItemIndex();

        if (refactorItemIndex == 0){
            auto phoneNumber = subWindow->getRefactorLine().toStdString();
            BookUnit::toFormat(phoneNumber);
            iter->addPhoneNumber(phoneNumber);
        }else if (refactorItemIndex == 1){
            (*(iter->getFullName()))[0] = subWindow->getRefactorLine().toStdString();
            *(iter->getEmail()) = subWindow->getNewEmailLine().toStdString();
        }else if (refactorItemIndex == 2){
            (*(iter->getFullName()))[1] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 3){
            (*(iter->getFullName()))[2] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 4){
            (*(iter->getAddress()))[0] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 5){
            (*(iter->getAddress()))[1] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 6){
            (*(iter->getAddress()))[2] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 7){
            (*(iter->getAddress()))[3] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 8){
            (*(iter->getAddress()))[4] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 9){
            (*(iter->getAddress()))[5] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 10){
            (*(iter->getAddress()))[6] = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 11){
            (*(iter->getBirthDate()))[0] = subWindow->getRefactorLine().toInt();
        }else if (refactorItemIndex == 12){
            (*(iter->getBirthDate()))[1] = subWindow->getRefactorLine().toInt();
        }else if (refactorItemIndex == 13){
            (*(iter->getBirthDate()))[2] = subWindow->getRefactorLine().toInt();
        }else if (refactorItemIndex == 14){
            *(iter->getEmail()) = subWindow->getRefactorLine().toStdString();
        }else if (refactorItemIndex == 15){
            auto phoneNumber = subWindow->getRefactorLine().toStdString();
            if (phoneNumber == "-" && iter->getPhoneNumberSize() == 1) {
                QMessageBox::warning(nullptr, "Ошибка",
                                     "Вы не можете удалить единственный номер!");
            }else if (phoneNumber == "-") {
                auto iterPhone = iter->getPhoneNumber()->begin();
                advance(iterPhone, subWindow->getRefactorPhoneNumberIndex());
                iter->getPhoneNumber()->erase(iterPhone);
            }else{
                BookUnit::toFormat(phoneNumber);
                iter->changePhoneNumber(phoneNumber, subWindow->getRefactorPhoneNumberIndex());
            }
        }

        updateTable();
    });

    subWindow->exec(); // открытие окна добавления
    subWindow->deleteLater(); // безопасное удаление окна
}

// слот для кнопки
void MainWindow::deleteBook() {
    auto *subWindow = new SubWindow(WindowMode::Delete, tableWidget, bookUnits, this);


    connect(subWindow, &SubWindow::accepted, this, [this, subWindow]() {
        tableWidget->removeRow(subWindow->getRow() - 1);

        auto iter = bookUnits->begin();
        advance(iter, subWindow->getRow() - 1);
        bookUnits->erase(iter);
        personIndex--;

        updateTable();
    });

    subWindow->exec(); // открытие окна добавления
    subWindow->deleteLater(); // безопасное удаление окна
}

// слот для кнопки
void MainWindow::loadData(){

    // Точно читать данные?
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите загрузить данные??",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    findBlock->clearSortStatus(); // Обнуляем статус сортировки

    // загрузжаем данный из файла (qt компилирует в build/*Kits*/, поэтому идём туда)
    //qtReadFile(FILENAME);
    Database db(bookUnits, this);
    personIndex = db.loadBookUnits();

    updateTable();

    // Обновляем счетчик
    personIndex = (unsigned int)(*bookUnits).size();
    //qWarning() << QString("Загружено %1 записей").arg(personIndex);
}

// слот для кнопки
void MainWindow::saveData(){

    // Точно соxранять данные?
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите сохранить данные?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    /*
    // Не забываем выйти в корневую папку проекта
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить файл", FILENAME, "Text files (*.txt)");

    qtWrite(filename);
    */
    Database db(bookUnits, this);
    db.saveBookUnits();


    //qWarning() << QString("Сохранено %1 записей").arg(personIndex);

}

//Функция чтения из файла
void MainWindow::qtReadFile(const QString& filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Ошибка открытия файла для чтения:" << file.errorString();
        QMessageBox::warning(nullptr, "Ошибка",
                             "Не удалось открыть файл для чтения:\n" + file.errorString());
        return;
    }

    bookUnits->clear();
    personIndex = 0;

    QTextStream in(&file);

    //int lineCount = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (!line.isEmpty()) {
            BookUnit unit;
            unit.fromString(line.toStdString());
            bookUnits->push_back(unit);
            //lineCount++;
            personIndex++;
        }
    }

    file.close();

    //qDebug() << "Чтение завершено! Прочитано записей:" << lineCount;
    return;
}


// Функция записи в файл
void MainWindow::qtWrite(const QString& filename) {

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Ошибка открытия файла для записи:" << file.errorString();
        QMessageBox::warning(nullptr, "Ошибка",
                             "Не удалось открыть файл для записи:\n" + file.errorString());
        return;
    }

    QTextStream out(&file);

    //int writeCount = 0;
    for (const auto& unit : *bookUnits) {
        if (!unit.isEmpty()){
            QString line = QString::fromStdString(unit.toString());
            out << line << "\n";
            //writeCount++;
        }
    }

    file.close();

    //qDebug() << "Запись завершена! Записано записей:" << writeCount;
}
