#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

#include "BookUnit.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(list<BookUnit> *bookUnits, QObject *parent = nullptr);
    ~Database();

    void saveBookUnits();
    int loadBookUnits();

private:
    bool createConnection(const QString& host = "localhost",
                          const QString& dbName = "postgres",
                          const QString& user = "postgres",
                          const QString& password = "Ch1b1s3116)",
                          int port = 5432);
    bool disconnect();
    bool isConnected() const;

    bool createTable();



    QSqlDatabase *db = nullptr;
    list<BookUnit> *bookUnits;

};

#endif // DATABASE_H
