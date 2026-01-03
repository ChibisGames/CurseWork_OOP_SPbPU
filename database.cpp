#include <QDebug>
#include <QSqlQuery>

#include "database.h"


Database::Database(list<BookUnit> *bookUnits, QObject *parent) : QObject(parent), bookUnits(bookUnits){
    if (!createConnection()){
        qDebug("Error init database");
    }

}

Database::~Database()
{
    disconnect();
    if (db) {
        delete db;
        db = nullptr;
    }
}

bool Database::createConnection(const QString& host,
                                const QString& dbName,
                                const QString& user,
                                const QString& password,
                                int port){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db->setHostName(host);
    db->setDatabaseName(dbName);
    db->setUserName(user);
    db->setPassword(password);
    db->setPort(port);

    if (!db->open()) {
        qDebug() << "Failed to open database:" << db->lastError().text();
        return false;
    }
    qDebug() << "Database opened successfully";
    return createTable();
}

bool Database::disconnect()
{
    if (isConnected()) {
        db->close();
        qDebug() << "Database disconnected";
        return true;
    }
    return false;
}

bool Database::isConnected() const
{
    return db && db->isOpen();
}

bool Database::createTable()
{
    QSqlQuery query(*db);

    return query.exec("CREATE TABLE IF NOT EXISTS bookUnits ("
                              "id SERIAL PRIMARY KEY,"
                              "first_name TEXT,"
                              "middle_name TEXT,"
                              "last_name TEXT,"
                              "addr1 TEXT, addr2 TEXT, addr3 TEXT, addr4 TEXT, addr5 TEXT, addr6 TEXT, addr7 TEXT,"
                              "birth_year INTEGER, birth_month INTEGER, birth_day INTEGER,"
                              "email TEXT,"
                              "phones TEXT)");
    qDebug("Table created!");
}

void Database::saveBookUnits()
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return;
    }

    // Очищаем таблицу
    QSqlQuery clearQuery(*db);
    clearQuery.exec("DELETE FROM bookUnits");

    // Подготавливаем запрос
    QString sql =
        "INSERT INTO bookUnits ("
        "first_name, middle_name, last_name,"
        "addr1, addr2, addr3, addr4, addr5, addr6, addr7,"
        "birth_year, birth_month, birth_day,"
        "email, phones"
        ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    QSqlQuery query(*db);
    query.prepare(sql);

    for (BookUnit& unit : *bookUnits) {
        // ФИО
        for (int i = 0; i < 3; i++) {
            QString value = QString::fromStdString(
                i < 3 ? (*unit.getFullName())[i] : ""
                );
            query.addBindValue(value);
        }

        // Адрес (7 полей)
        for (int i = 0; i < 7; i++) {
            QString value = QString::fromStdString(
                i < 7 ? (*unit.getAddress())[i] : ""
                );
            query.addBindValue(value);
        }

        // Дата рождения
        for (int i = 0; i < 3; i++) {
            int value = i < 3 ? (*unit.getBirthDate())[i] : 0;
            query.addBindValue(value);
        }

        // Email
        query.addBindValue(QString::fromStdString(*unit.getEmail()));

        // Телефоны (объединяем в одну строку через запятую)
        QString phones;
        for (const string& phone : (*unit.getPhoneNumber())) {
            if (!phones.isEmpty()) phones += ",";
            phones += QString::fromStdString(phone);
        }
        query.addBindValue(phones);

        if (!query.exec()) {
            qDebug() << "Save error:" << query.lastError().text();
        }
    }
    qDebug("DATA SAVED");
}

int Database::loadBookUnits()
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return -1;
    }

    bookUnits->clear();
    int personIndex = 0;

    QSqlQuery query("SELECT * FROM bookUnits", *db);

    while (query.next()) {
        BookUnit unit;

        // Читаем ФИО (поля 1-3)
        for (int i = 0; i < 3; i++) {
            if (i < 3) {
                (*unit.getFullName())[i] = query.value(i + 1).toString().toStdString();
            }
        }

        // Читаем адрес (поля 4-10)
        for (int i = 0; i < 7; i++) {
            if (i < 7) {
                (*unit.getAddress())[i] = query.value(i + 4).toString().toStdString();
            }
        }

        // Читаем дату рождения (поля 11-13)
        for (int i = 0; i < 3; i++) {
            if (i < 3) {
                (*unit.getBirthDate())[i] = query.value(i + 11).toInt();
            }
        }

        // Читаем email (поле 14)
        *unit.getEmail() = query.value(14).toString().toStdString();

        // Читаем телефоны (поле 15)
        QString phonesStr = query.value(15).toString();
        if (!phonesStr.isEmpty()) {
            QStringList phonesList = phonesStr.split(",");
            for (const QString& phone : phonesList) {
                if (!phone.trimmed().isEmpty()) {
                    unit.addPhoneNumber(phone.trimmed().toStdString());
                }
            }
        }

        bookUnits->push_back(unit);
        personIndex++;
    }

    return personIndex;
}
