#ifndef QTMODEL_H
#define QTMODEL_H

#include <QObject>
#include <QWidget>
#include<QTableWidget>

#include<BookUnit.h>

int qtMainMenu();

QTableWidget* createQtTable(QWidget *window);

void addBookUnitToTable(QTableWidget* tableWidget, const BookUnit& bookUnit, int row);

void updateQtTable (QTableWidget *tableWidget);


#endif // QTMODEL_H
